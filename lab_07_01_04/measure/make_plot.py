from matplotlib import pyplot as plt

with open("./out/preproc_data.txt", "r") as file:
    xmy = []
    ymy = []
    xq = []
    yq = []
    curr = 0
    for line in file:
        if line == "next\n":
            curr += 1
        else:
            if curr == 1:
                length, time = line.split()
                time = float(time)
                length = int(length)
                xmy.append(length)
                ymy.append(time)
            elif curr == 0:
                length, time = line.split()
                time = float(time)
                length = int(length)
                xq.append(length)
                yq.append(time)


plt.xlabel("Длина массива")
plt.ylabel("Время выполнения сортировки")
plt.title("qsort и bublesort")
plt.plot(xmy, ymy)
plt.plot(xq, yq)
plt.savefig("./out/sort.png")
plt.close()
