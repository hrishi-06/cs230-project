import re
from matplotlib import pyplot as plt

text = str

heirarchies = ["NINE", "INCLUSIVE", "EXCLUSIVE"]
repl_policies = ["lru", "lfu", "drrip", "random", "hawkeye", "fifo", "mfu"]

y = []
for heirarchy in heirarchies:
    x = []
    for policy in repl_policies:
        with open(f'bfs-3.trace.gz-bimodal-no-no-no-no-{policy}-1core-{heirarchy}.txt', 'r') as file:
            text = file.read().replace('\n', '')
        
        match = re.search(r"CPU 0 cumulative IPC: ([0-9]+\.[0-9]+)", text)
        ipc_value = float(match.group(1))
        x.append(ipc_value)
    
    y.append(x)

for i in range(len(heirarchies)):
    plt.plot(repl_policies, y[i], marker = 'x')

plt.legend(heirarchies)
plt.ylabel("IPC")
plt.xlabel("Replacement Policy")
plt.show()
