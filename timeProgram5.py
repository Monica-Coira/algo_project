
import subprocess
import matplotlib.pyplot as plt
import time
import random
import statistics

K = 3
SIZE_INPUTS = list(range(10000, 100001, 10000))
NUM_RUNS = 7
timesPerSize = []

random.seed(42)

# Generate input files
for n in SIZE_INPUTS:
    with open("input_" + str(n) + ".txt", "w") as file:
        file.write(str(n) + " " + str(K) + "\n")

        for i in range(n):
            file.write(str(random.randint(1, 99999)) + "\n")

# Benchmark Program 5
for n in SIZE_INPUTS:
    timesPerRun = []
    filename = "input_" + str(n) + ".txt"

    # Warm-up run (not included in measurements)
    with open(filename, "r") as file:
        subprocess.run(
            ["./program5"],
            stdin=file,
            stdout=subprocess.DEVNULL,
            check=True
        )

    # Run the program multiple times
    for attempt in range(NUM_RUNS):
        with open(filename, "r") as file:
            startTime = time.perf_counter()

            subprocess.run(
                ["./program5"],
                stdin=file,
                stdout=subprocess.DEVNULL,
                check=True
            )

            endTime = time.perf_counter()

        timesPerRun.append((endTime - startTime) * 1000)

    # Use the median running time
    medianTime = statistics.median(timesPerRun)
    timesPerSize.append(medianTime)

    print("n =", n, " time =", round(medianTime, 2), "ms")

# Plot results
plt.plot(SIZE_INPUTS, timesPerSize, marker="o")
plt.xlabel("Input Size (n)")
plt.ylabel("Running Time (ms)")
plt.title("Program 5 Input Size vs Running Time")
plt.xticks(SIZE_INPUTS, rotation=45)
plt.grid(True)
plt.tight_layout()
plt.savefig("plotProgramFive.png", dpi=200)
plt.show()
