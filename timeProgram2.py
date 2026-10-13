import subprocess
import matplotlib.pyplot as plt
import time

SIZE_INPUTS = list(range(50000, 500001, 50000))
timesPerSize = []

for n in SIZE_INPUTS:
    timesPerRun = []
    for attempt in range(5):
        file = open("input2_" + str(n) + ".txt")
        startTime = time.perf_counter()
        subprocess.run(["./program2.exe"], stdin=file, stdout=subprocess.DEVNULL)
        endTime = time.perf_counter()
        file.close()
        timesPerRun.append((endTime - startTime) * 1000)
    timesPerRun.sort()
    timesPerSize.append(timesPerRun[2])
    print("n =", n, " time =", round(timesPerRun[2], 1), "ms")

plt.plot(SIZE_INPUTS, timesPerSize, marker="o")
plt.xlabel("Input size")
plt.ylabel("Running time (ms)")
plt.title("Program 2 Input Size vs Running Time")
plt.grid(True)
plt.savefig("plotProgramTwo.png", dpi=200)