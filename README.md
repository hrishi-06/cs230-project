# Exploring Cache Hierarchy for Graphs
### Team Name - **ArchiOptimizers**
### Team Members - 
1. Avadhoot Jadhav (210050027)
2. Megh Gohil (210050055)
3. Hrishikesh Jedhe Deshmukh (210050073)
****

## Cache Hierarchy
We modified champsim and added additional cache hierarchies as a part of CS230 project. 

This modified champsim now supports:
1. Inclusive Cache Hierarchy (`INCLUSIVE`)
2. Exclusive Cache Hierarachy (`EXCLUSIVE`)
3. Non-Inclusive Non-Exclusive Cache Hierarchy (`NINE`)
****

## Replacement Policies
You can use following replacement policies for LLC:

1. Least Recently Used (`lru`)
2. Least Frequently Used (`lfu`)
3. First In First Out (`fifo`)
4. LRU + LFU (`lrfu`)
5. Hawkeye (`hawkeye`)
6. Most Frequently Used (`mfu`)
7. LFU with Ageing Counter (`age`)
8. Random (`random`) 
9. DRRIP (`drrip`)
****

## Compile
ChampSim takes eight parameters: Branch predictor, L1I prefetcher, L1D prefetcher, L2C prefetcher, LLC prefetcher, LLC replacement policy, the number of cores and cache hierarchy. 
```
$ ./build_champsim.sh [BRANCH] [L1I_PREFETCHER] [L1D_PREFETCHER] [L2C_PREFETCHER] [LLC_PREFETCHER] [LLC_REPLACEMENT] [NUM_CORE] [HIERARCHY]
```
> `[HEIRARCHY]` can be either `NINE` or `INCLUSIVE` or `EXCLUSIVE`

For example, `./build_champsim.sh bimodal no no no no lru 1 NINE` builds a single-core processor with bimodal branch predictor, no L1/L2 data prefetchers, and the baseline LRU replacement policy for the LLC with NINE hierarchy.
```
$ ./build_champsim.sh bimodal no no no no lru 1 NINE
```
****

## Running Simulations
Execute `run_champsim.sh` with proper input arguments. The default TRACE_DIR in run_champsim.sh is set to $PWD/../traces.
```
$ ./run_champsim.sh [BINARY] [N_WARM] [N_SIM] [TRACE] [OPTION]
```