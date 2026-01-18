#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "errors.h"
#include "darray_op.h"

#define LEN_START 100
#define LEN_STEP 500
#define MAX_LEN 10500
#define MAX_MEASURMENTS 10000

#define ERR_GET_TIME 101


/*
Функция высчитывает величину RSE для массива времён выполнения.
Принимает на вход long массив длиной более 1, size_t длину массива
*/
double calc_rse(const unsigned long data[], size_t data_n)
{
    assert(data_n >= 2);

    unsigned long long sum = 0;
    double err, avg, sum_sq = 0;
    // Сумма
    for (size_t i = 0; i < data_n; i++)
        sum += data[i];
    // Среднее значение
    avg = (double) sum / data_n;
    // Сумма квадратов отклонений
    for (size_t i = 0; i < data_n; i++)
        sum_sq += (data[i] - avg) * (data[i] - avg);
    // Стандартная ошибка
    err = sqrt(sum_sq / (data_n - 1)) / sqrt(data_n);
    // Возвращаемое значение - RSE (в процентах)
    return (err / avg) * 100;
}


/*
Функция выводит значения измерения в милисекундах, заканчивая пустой строкой.
Принимаерт на вход unsigned long массив, size_t его размер и size_t длину измеряемого массива
*/
void print_measurments(const unsigned long array[], size_t array_n, size_t n, double rse)
{
    for (size_t i = 0; i < array_n; i++)
        printf("%zu %.2lf %zu %.2lf\n", n, ((double) array[i]) / 1000000, array_n, rse);
    printf("\n");
}


/*
Функция заполняет массив псевдослучайными целыми числами.
Принимает на вход int массив, и size_t его длину
*/
void fill_rand_array(int array[], size_t array_n)
{
    for (size_t i = 0; i < array_n; i++)
        array[i] = rand();
}


/*
Функция выполняет операцию присваивания для массива.
Принимает на вход int массив-источник, int массив-назначение, size_t их длину
*/
void array_copy(const int src[], int dst[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        dst[i] = src[i];
}


/*
Функция возвращает разницу между двумя точками во времени в наносекундах.
Принимает на вход struct timespec указатели на начало и конец промежутка
*/
unsigned long time_difference(const struct timespec *time_b, const struct timespec *time_e)
{
    return (time_e->tv_sec - time_b->tv_sec) * 1000000000 + (time_e->tv_nsec - time_b->tv_nsec);
}


int measure(size_t max_array_len, size_t len_start, size_t len_step, void (*sort)(void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*)))
{
    int memory_array[MAX_LEN], work_array[MAX_LEN];
    size_t meas_i = 0;
    unsigned long curr_measurments_data[MAX_MEASURMENTS];
    struct timespec time_b, time_e;
    double rse = 100.0;

    // Установка seed, чтобы при каждом запуске программы исследовалась сортировка одинаковых массивов
    srand(max_array_len);
    // Длина массива начинаеся со 100 и увеличивается с шагом 500
    for (size_t n = len_start; n <= max_array_len; n += len_step)
    {
        // Заполнение массива случайными числами
        fill_rand_array(memory_array, n);
        do
        {
            // Заполнение массива данными заново
            array_copy(memory_array, work_array, n);
            // Измерение времени работы
            if (clock_gettime(CLOCK_MONOTONIC_RAW, &time_b))
                return ERR_GET_TIME;
            sort(work_array, n, sizeof(int), cmp_uni_int);
            if (clock_gettime(CLOCK_MONOTONIC_RAW, &time_e))
                return ERR_GET_TIME;
            curr_measurments_data[meas_i] = time_difference(&time_b, &time_e);
            meas_i += 1;
            // 5 измерений гарантированно произойдут
            if (meas_i > 5)
                rse = calc_rse(curr_measurments_data, meas_i);
        } while (rse >= 1.0 && meas_i <= MAX_MEASURMENTS);
        print_measurments(curr_measurments_data, meas_i, n, rse);
        // Возвращение к исходному состоянию перед замером с другой длиной массива
        meas_i = 0;
        rse = 100.0;
    }
    return OK;
}


int main(int argc, char **argv)
{
    size_t max_array_len;
    int rc = OK;
    
    // Проверка на корректность использования
    if (argc != 2)
    {
        printf("Usage: %s [max_array_len]\n", argv[0]);
        return ERR_ARGS;
    }
    max_array_len = (size_t) atoi(argv[1]);
    // Проверка на корректность максимальной длины сортируемого массива
    if (max_array_len < 100 || max_array_len > MAX_LEN)
    {
        printf("Wrong max_array_len\n");
        return ERR_RANGE;
    }
    
    rc = measure(max_array_len, LEN_START, LEN_STEP, qsort);
    if (rc != OK)
        return rc;
    printf("next\n");
    rc = measure(max_array_len, LEN_START, LEN_STEP, mysort);

    return OK;
}







