import random
K = 3
SIZE_INPUTS = list(range(50000, 500001, 50000))

for n in SIZE_INPUTS:
    p = random.randint(2, n - 1)
    left = []
    for i in range(p - 1):
        left.append(random.randint(1, 99998))
    left.sort()
    right = []
    for i in range(n - p):
        right.append(random.randint(1, 99998))
    right.sort(reverse=True)
    costs = left + [99999] + right
    file = open("input2_" + str(n) + ".txt", "w")
    file.write(str(n) + " " + str(K) + "\n")
    for cost in costs:
        file.write(str(cost) + " ")
    file.write("\n")
    file.close()