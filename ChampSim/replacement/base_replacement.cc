#include "cache.h"

#define AGE_THRESHOLD 13
#define FREQ_THRESHOLD 5

uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    // baseline LRU replacement policy for other caches
    return lru_victim(cpu, instr_id, set, current_set, ip, full_addr, type);
}

uint32_t CACHE::random_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            return way;
        }
    }
    return rand() % NUM_WAY;
}

uint32_t CACHE::seq_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    static vector<uint32_t> arr(NUM_SET, 0);

    uint32_t ret = arr.at(set);

    arr.at(set) = (arr.at(set) + 1) % NUM_WAY;

    return ret;
}

uint32_t CACHE::fifo_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            return way;
        }
    }

    if (way == NUM_WAY)
    {
        for (way = 0; way < NUM_WAY; way++)
        {
            if (block[set][way].lru == NUM_WAY - 1)
            {
                break;
            }
        }
    }

    return way;
}

uint32_t CACHE::age_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            return way;
        }
    }

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].age > AGE_THRESHOLD && block[set][way].lru < FREQ_THRESHOLD)
        {
            return way;
        }
    }

    uint32_t freq = INT_MAX;
    uint32_t ret_way = -1;

    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        if (block[set][i].lru < freq)
        {
            freq = block[set][i].lru;
            ret_way = i;
        }
    }

    return ret_way;
}

uint32_t CACHE::lfu_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            return way;
        }
    }

    uint32_t freq = INT_MAX;
    uint32_t ret_way = -1;

    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        if (block[set][i].lru < freq)
        {
            freq = block[set][i].lru;
            ret_way = i;
        }
    }

    return ret_way;
}

uint32_t CACHE::mfu_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;
    // cout << "endlggewgh" << endl;
    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            // cout << "empty block already exists" << endl;
            return way;
        }
    }
    // cout << "are we going to egt a seg fault???\n";
    uint32_t freq = 0;
    uint32_t ret_way = -1;

    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        int temp = block[set][i].lru;
        temp = temp / 65536 + temp % 65536;
        if (temp > freq)
        {
            freq = temp;
            // cout <<"return way of mfu in loop : " <<ret_way <<endl;
            ret_way = i;
        }
    }
    // cout <<"return way of mfu : " <<ret_way <<endl;
    return ret_way;
}

uint32_t CACHE::lrfu_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
	uint32_t way = 0;
     for (way=0; way<NUM_WAY; way++) {
         if (block[set][way].valid == false) {
            // cout << "way value returned : " << way << endl;
             return way;
        }
     }
    // cout << "no empty found\n";
	uint32_t freq = INT_MAX;
	uint32_t ret_way = -1;
	for(int i = 0; i<NUM_WAY; i++) {
        int temp = block[set][i].lru/65536;
        temp += NUM_WAY - block[set][i].lru%65536;
        if(temp < freq){
            freq = temp;
            ret_way = i;
        }
	}
    // cout << "the victim is : " << ret_way << endl;
	return ret_way;
}

uint32_t CACHE::optgen_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {
            return way;
        }
    }

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].lru == 7)
        {
            return way;
        }
    }

    uint32_t max = 0;
    uint32_t max_way = 0;

    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].lru > max)
        {
            max = block[set][way].lru;
            max_way = way;
        }
    }

    return max_way;
}

void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    if (type == WRITEBACK)
    {
        if (hit) // wrietback hit does not update LRU state
            return;
    }

    return lru_update(set, way);
}

uint32_t CACHE::lru_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    // fill invalid line first
    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {

            DP(if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY)
    {
        for (way = 0; way < NUM_WAY; way++)
        {
            if (block[set][way].lru == NUM_WAY - 1)
            {

                DP(if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " lru: " << block[set][way].lru << endl; });

                break;
            }
        }
    }

    if (way == NUM_WAY)
    {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }

    return way;
}

void CACHE::lru_update(uint32_t set, uint32_t way)
{
    // update lru replacement state
    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        if (block[set][i].lru < block[set][way].lru)
        {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = 0; // promote to the MRU position
}

void CACHE::fifo_update(uint32_t set, uint32_t way)
{
    // update lru replacement state
    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        block[set][i].lru++;
    }
    block[set][way].lru = 0; // promote to the MRU position
}

void CACHE::lfu_update(uint32_t set, uint32_t way, uint8_t hit)
{
    if (!hit)
    {
        block[set][way].lru = 0; // promote to the MRU position
    }
    else
    {
        block[set][way].lru += 1;
    }
}

void CACHE::lrfu_update(uint32_t set, uint32_t way, uint8_t hit)
{
	if(! hit) {
    	block[set][way].lru = 65536; // promote to the MRU position
	}
	else{
		block[set][way].lru += 65536;
	}

    for (uint32_t i=0; i<NUM_WAY; i++) {
        if ((block[set][i].lru) % 65536 < (block[set][way].lru) % 65536) {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = block[set][way].lru/65536; // promote to the MRU position
    block[set][way].lru = block[set][way].lru*65536;
}

void CACHE::age_update(uint32_t set, uint32_t way, uint8_t hit)
{
    if (!hit)
    {
        block[set][way].lru = 0; // promote to the MRU position
        block[set][way].age = 0;
    }
    else
    {
        block[set][way].lru += 1;
    }

    // for (uint32_t j = 0; j < NUM_SET; ++j)
    // {
    //     for (uint32_t i = 0; i < NUM_WAY; ++i)
    //     {
    //         if (block[j][i].valid)
    //         {
    //             block[j][i].age++;
    //         }
    //     }
    // }

    for (uint32_t i = 0; i < NUM_WAY; ++i)
    {
        if (block[set][i].valid)
        {
            block[set][i].age++;
        }
    }
}

void CACHE::mfu_update(uint32_t set, uint32_t way, uint8_t hit)
{
    if (!hit)
    {
        block[set][way].lru = 65536; // promote to the MRU position
    }
    else
    {
        block[set][way].lru += 65536;
    }

    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        if ((block[set][i].lru) % 65536 < (block[set][way].lru) % 65536)
        {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = block[set][way].lru / 65536; // promote to the MRU position
    block[set][way].lru = block[set][way].lru * 65536;
}

void CACHE::optgen_update(uint32_t set, uint32_t way, uint64_t addr, uint64_t ip, uint8_t xhit, uint64_t ev_addr)
{
    static uint32_t HISTORY_SIZE = 32 * NUM_WAY;
    static vector<vector<uint32_t>> history(NUM_SET, vector<uint32_t>(HISTORY_SIZE, 0));
    static vector<vector<uint64_t>> history_addr(NUM_SET, vector<uint64_t>(HISTORY_SIZE, 0));
    static vector<vector<uint64_t>> history_ip(NUM_SET, vector<uint64_t>(HISTORY_SIZE, 0));
    static vector<uint32_t> indx(NUM_SET, 0);
    static vector<uint32_t> size(NUM_SET, 0);
    static std::hash<uint64_t> h;
    const uint32_t SIZE_IP_HISTORY = 32768;
    static vector<uint64_t> ip_table(SIZE_IP_HISTORY, 0);

    uint32_t curr_indx = indx.at(set);
    uint32_t curr_size = size.at(set);

    history_addr.at(set).at(curr_indx) = addr;
    history.at(set).at(curr_indx) = 0;
    history_ip.at(set).at(curr_indx) = ip;

    curr_indx = (curr_indx + 1) % (HISTORY_SIZE);

    if (curr_size != HISTORY_SIZE)
    {
        curr_size++;
    }

    uint32_t last_indx;
    uint8_t flag = 0;

    for (uint32_t i = 1; i <= curr_size; ++i)
    {
        uint32_t indexxx = (HISTORY_SIZE + curr_indx - i) % (HISTORY_SIZE);

        if (history_addr.at(set).at(indexxx) == addr)
        {
            last_indx = indexxx;
            flag = 1;
            break;
        }
    }

    uint8_t hit = 1;

    if (flag)
    {
        for (uint32_t i = 1; i <= curr_size; ++i)
        {
            uint32_t indexxx = (HISTORY_SIZE + curr_indx - i) % (HISTORY_SIZE);

            if (history.at(set).at(indexxx) >= NUM_WAY)
            {
                hit = 0;
                break;
            }
        }
    }

    if (hit)
    {
        for (uint32_t i = 1; i <= curr_size; ++i)
        {
            uint32_t indexxx = (HISTORY_SIZE + curr_indx - i) % (HISTORY_SIZE);

            if (indexxx == last_indx)
            {
                history.at(set).at(indexxx)++;
                break;
            }

            history.at(set).at(indexxx)++;
        }
    }

    if (flag)
    {
        uint32_t in = h(history_ip.at(set).at(last_indx)) % SIZE_IP_HISTORY;
        if (hit)
        {
            ip_table.at(in)++;
        }
        else
        {
            ip_table.at(in)--;
        }
    }

    if (xhit)
    {
        uint32_t in = h(ip) % SIZE_IP_HISTORY;
        uint32_t averse = ip_table.at(in) >> 2;

        if (averse > 1)
        {
            block[set][way].lru = 0;
        }
        else
        {
            block[set][way].lru = 7;
        }
    }
    else
    {
        uint32_t in = h(ip) % SIZE_IP_HISTORY;
        uint32_t averse = ip_table.at(in) >> 2;

        if (averse > 1)
        {
            block[set][way].lru = 0;
        }
        else
        {
            block[set][way].lru = 7;

            for (uint32_t i = 0; i < NUM_WAY; ++i)
            {
                if (block[set][i].lru < 7)
                {
                    block[set][i].lru++;
                }
            }
        }
    }

    for (uint32_t i = 1; i <= curr_size; ++i)
    {
        uint32_t indexxx = (HISTORY_SIZE + curr_indx - i) % (HISTORY_SIZE);

        uint32_t in;
        if (history_addr.at(set).at(indexxx) == ev_addr)
        {
            in = h(history_ip.at(set).at(indexxx)) % SIZE_IP_HISTORY;
            ip_table.at(in) = 0;
            break;
        }
    }
}

void CACHE::replacement_final_stats()
{
}

#ifdef NO_CRC2_COMPILE
void InitReplacementState()
{
}

uint32_t GetVictimInSet(uint32_t cpu, uint32_t set, const BLOCK *current_set, uint64_t PC, uint64_t paddr, uint32_t type)
{
    return 0;
}

void UpdateReplacementState(uint32_t cpu, uint32_t set, uint32_t way, uint64_t paddr, uint64_t PC, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
}

void PrintStats_Heartbeat()
{
}

void PrintStats()
{
}
#endif
