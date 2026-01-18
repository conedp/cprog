from statistics import *

measure_avg_times_q = []
measure_lengths_q = []
measure_avg_times_my = []
measure_lengths_my = []

# Данные о времени для текущей длины
measure_curr_times_q = []
measure_curr_times_my = []

file_open = "./out/measure_data.txt"
file_save = "./out/preproc_data.txt"
curr = 0
# Обработка измерений в милисекундах внутри программы, сортировка реализована с помощью формальной замены индексации
with open(file_open, "r") as file:
    for line in file:
        if line == "next\n":
            curr += 1
        elif line != "\n":
            array_n, time, meas_num, rse = line.split()
            if curr == 0:
                measure_curr_times_q.append(float(time))
            elif curr == 1:
                measure_curr_times_my.append(float(time))
        else:
            if curr == 0:
                measure_lengths_q.append(array_n)
                measure_avg_times_q.append(mean(measure_curr_times_q))
                measure_curr_times_q = []
            elif curr == 1:
                measure_lengths_my.append(array_n)
                measure_avg_times_my.append(mean(measure_curr_times_my))
                measure_curr_times_my = []


with open(file_save, "w") as file:
    for i in range(len(measure_avg_times_q)):
        print(f"{measure_lengths_q[i]} {measure_avg_times_q[i]}", file=file)

    print("next", file=file)
    for i in range(len(measure_avg_times_my)):
        print(f"{measure_lengths_my[i]} {measure_avg_times_my[i]}", file=file)


