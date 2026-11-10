import subprocess
import matplotlib.pyplot as plt
import time

SIZE_INPUTS = [10000, 30000, 50000, 70000, 90000, 99999]
timesPerSize = []

for n in SIZE_INPUTS:
    timesPerRun = []
    for attempt in range(3):                       
        file = open("input_" + str(n) + ".txt")
        startTime = time.perf_counter()
        subprocess.run(["./program5"], stdin=file, stdout=subprocess.DEVNULL, check=True)
        endTime = time.perf_counter()
        file.close()
        timesPerRun.append((endTime - startTime) * 1000)
    timesPerRun.sort()                                
    timesPerSize.append(timesPerRun[1])               
    print("n =", n, " time =", round(timesPerRun[1], 1), "ms")

plt.plot(SIZE_INPUTS, timesPerSize, marker="o")
plt.xlabel("Input size")
plt.ylabel("Running time (ms)")
plt.title("Program 5 Input Size vs Running Time")
plt.grid(True)
plt.savefig("plotProgramFive.png", dpi=200)
plt.show()