/*
Сформировать и вывести на экран новый массив, в который сначала скопировать элементы исходного массива, являющиеся числами Армстронга.
*/
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_SUITABLE 3

#define N 10


/*
Функция печатает в stdin её описание.
Принимает на вход int код ошибки.
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
Функция печатает массив в stdout через пробел.
Принимает на вход int массив и size_t его длину
*/
void print_array(const int a[], size_t a_n)
{
    printf("array: ");
    for (size_t i = 0; i < a_n; i++)
        printf("%d ", a[i]);
    puts("");
}


/*
Функция возвращает число цифр в нём.
Принимает на вход int число
*/
unsigned int digit_len(int k)
{
    k = abs(k);
    const unsigned int base = 10;
    unsigned int len = 1;
    if (k == 0)
        return 0;
    while (k != 0)
    {
        if (k / base != 0)
            len += 1;
        k /= base;
    }
    return len;
}   



/*
Функция возвращает int основание в степени показатель.
Принимает на вход int основание и int положительный показатель
*/
int power(int a, int n)
{
    int z = a, ans = 1;
    int mask = 1;

    for (size_t i = 1; mask <= n && i < sizeof(a)*CHAR_BIT; i++)
    {
        if (mask & n)
        {
            ans *= z;
            z *= z;   
        }
        else
            z *= z;
        mask <<= 1;
    }
    return ans;
}



/*
Функция возвращает uint сумму цифр числа, возведённых в степень его длины.
Принимает на вход int число
*/
unsigned int do_ppdi(int n)
{
    unsigned int m = digit_len(n);
    const unsigned int base = 10;
    unsigned int sum = 0;
    n = abs(n);
    while (n != 0)
    {
        sum += power(n % base, m);
        n /= base;
    }
    return sum;
}


/*
Функция возвращает bool: является ли число числом Армстронга.
Принимает на вход int число
*/
bool is_ppdi(int n)
{
    if (n <= 0)
        return false;
    else if ((unsigned) n == do_ppdi(n))
        return true;
    else
        return false;
}


/*
Функция копирует во второй те числа из первого, которые яаляются числами Армстронга..
Принмиает на вход int массив первый, и size_t длину первого, int массив второй, указатель на size_t длину второго
*/
int copy_ppdi(const int a[], const size_t a_n, int b[], size_t *b_n)
{
    *b_n = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        if (is_ppdi(a[i]))
        {
            b[*b_n] = a[i];
            *b_n += 1;
        }
    }
    return OK;
}


int main(void)
{
    int a[N], b[N];
    int rc;
    size_t a_n, b_n;
    
    if ((rc = input_array(a, &a_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    copy_ppdi(a, a_n, b, &b_n);
    if (b_n == 0)
    {
        print_error(ERR_NO_SUITABLE);
        return ERR_NO_SUITABLE;
    }
    print_array(b, b_n);
    return OK;
}
