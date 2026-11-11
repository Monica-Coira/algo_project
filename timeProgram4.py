import subprocess
import matplotlib.pyplot as plt
import time

SIZE_INPUTS = list(range(10000, 100001, 10000))

PROGRAMS = [("program4A", "plotProgramFourA.png", "Program 4A"),
            ("program4B", "plotProgramFourB.png", "Program 4B")]

for program, imageName, title in PROGRAMS:
    timesPerSize = []

    for n in SIZE_INPUTS:
        timesPerRun = []

        for attempt in range(3):
            file = open("input4_" + str(n) + ".txt")
            startTime = time.perf_counter()
            subprocess.run(["./" + program], stdin=file, stdout=subprocess.DEVNULL, check=True)
            endTime = time.perf_counter()
            file.close()
            timesPerRun.append((endTime - startTime) * 1000)

        timesPerRun.sort()
        timesPerSize.append(timesPerRun[1])
        print(title, " n =", n, " time =", round(timesPerRun[1], 1), "ms")

    plt.figure()
    plt.plot(SIZE_INPUTS, timesPerSize, marker="o")
    plt.xlabel("Input size")
    plt.ylabel("Running time (ms)")
    plt.title(title + " Input Size vs Running Time (k = ceil(n/10))")
    plt.grid(True)
    plt.savefig(imageName, dpi=200)

plt.show()