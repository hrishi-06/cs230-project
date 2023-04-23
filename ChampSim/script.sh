trace="cc-6.trace.gz"

./build_champsim.sh bimodal no no no no lru 1 NINE
./build_champsim.sh bimodal no no no no lru 1 INCLUSIVE
./build_champsim.sh bimodal no no no no lru 1 EXCLUSIVE

./build_champsim.sh bimodal no no no no lfu 1 NINE
./build_champsim.sh bimodal no no no no lfu 1 INCLUSIVE
./build_champsim.sh bimodal no no no no lfu 1 EXCLUSIVE

./build_champsim.sh bimodal no no no no drrip 1 NINE
./build_champsim.sh bimodal no no no no drrip 1 INCLUSIVE
./build_champsim.sh bimodal no no no no drrip 1 EXCLUSIVE

./build_champsim.sh bimodal no no no no fifo 1 NINE
./build_champsim.sh bimodal no no no no fifo 1 INCLUSIVE
./build_champsim.sh bimodal no no no no fifo 1 EXCLUSIVE

./run_champsim.sh bimodal-no-no-no-no-lru-1core-NINE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-lru-1core-INCLUSIVE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-lru-1core-EXCLUSIVE 30 60 $trace

./run_champsim.sh bimodal-no-no-no-no-lfu-1core-NINE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-lfu-1core-INCLUSIVE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-lfu-1core-EXCLUSIVE 30 60 $trace

./run_champsim.sh bimodal-no-no-no-no-drrip-1core-NINE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-drrip-1core-INCLUSIVE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-drrip-1core-EXCLUSIVE 30 60 $trace

./run_champsim.sh bimodal-no-no-no-no-fifo-1core-NINE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-fifo-1core-INCLUSIVE 30 60 $trace
./run_champsim.sh bimodal-no-no-no-no-fifo-1core-EXCLUSIVE 30 60 $trace