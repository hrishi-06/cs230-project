from multiprocessing import Process
import os

def run( LLC_repl:str, heirarchy:str, trace:str):
    cmd = f"./run_champsim.sh bimodal-no-no-no-no-{LLC_repl}-1core-{heirarchy} 30 60 {trace}"
    os.system(cmd)

LLC_repl_arr = ["lru", "lfu", "drrip"]
heirarchy_arr = ["NINE", "INCLUSIVE", "EXCLUSIVE"]
trace = "cc-6.trace.gz"

if __name__ == "__main__": # Here
    process_list = []

    for LLC_repl in LLC_repl_arr:
        for heirarchy in heirarchy_arr:
            process = Process(target=run, args=(LLC_repl, heirarchy, trace))
            process_list.append(process)
            process.start()

    for process in process_list:
        process.join()