import random
K = 3                                                 
SIZE_INPUTS = [10000, 30000, 50000, 70000, 90000, 99999]                                     

for n in SIZE_INPUTS:
    costs = []
    for i in range(n):
        costs.append(random.randint(1, 99999))
    
    costs.sort(reverse=True)
    file = open("input_" + str(n) + ".txt", "w")
    file.write(str(n) + " " + str(K) + "\n")
    for cost in costs:
        file.write(str(cost) + " ")
    file.write("\n")
    file.close()