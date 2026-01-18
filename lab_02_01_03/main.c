/*
Найти и вывести на экран среднее геометрическое положительных элементов массива
*/
#include <stdio.h>
#include <math.h>
#include <stddef.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_SUITABLE 3

#define N 10


/*
Функция печатает в stdin описание ошибки.
Принимает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == ERR_IO)
        puts("Input error");
    else if (rc == ERR_RANGE)
        puts("Range error");
    else if (rc == ERR_NO_SUITABLE)
        puts("No suitable error");
    else
        printf("Unknown error %d\n", rc);
}


/*
Функция считывает массив из stdin.
Принимает на вход int массив и size_t указатель на его длину
*/
int input_array(int a[], size_t *a_n)
{
    printf("Input length of array: ");
    if (scanf("%zu", a_n) != 1)
        return ERR_IO;
    if (*a_n == 0 || *a_n > N)
        return ERR_RANGE;
    printf("Input array: ");
    for (size_t i = 0; i < *a_n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}


/*
Функция находит среднее геометрическое и возвращает через указатель.
Принимает на вход int массив, size_t его длину и double указатель на среднее геметрическое
*/
int geometric_mean_of_pos(const int a[], const size_t a_n, double *gm)
{
    double gm_c = 1;
    size_t counter_pos = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        if (a[i] > 0)
        {
            counter_pos++;
            gm_c *= a[i];
        }
    }
    if (counter_pos == 0)
        return ERR_NO_SUITABLE;
    else
        *gm = pow(gm_c, 1.0 / counter_pos);
    return OK;
}


int main(void)
{
    int a[N];
    int rc;
    size_t n;
    double ans = 0;
    
    if ((rc = input_array(a, &n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    if ((rc = geometric_mean_of_pos(a, n, &ans)) != OK)
    {
        print_error(rc);
        return rc;
    }
    printf("Geometric mean of pos element = %lf\n", ans);
    return OK;
}
