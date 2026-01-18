/*
Вставить в исходный массив после каждого положительного элемента реверс этого же элемента.
Ситуацию, когда массив после операции не изменился, ошибочной не считать.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_OVERFLOW 3

#define N 10
#define DOUBLE_N (N*2)


/*
Функция печатает в stdin её описание.
Принимает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == ERR_IO)
        puts("Input error");
    else if (rc == ERR_RANGE)
        puts("Range error");
    else if (rc == ERR_OVERFLOW)
        puts("Overflow error");
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
Функция возвращает число цифр в числе.
Принимает на вход int положительное число
*/
unsigned int digit_len(int k)
{
    k = abs(k);
    const unsigned int base = 10;
    unsigned int len = 1;
    while (k != 0)
    {
        if (k / base != 0)
            len += 1;
        k /= base;
    }
    return len;
}


/*
Функция возвращает число с цифрами в обратном порядке (опуская ведущие нули).
Принимает на вход int положительное число
*/
int reverse_num(int *k)
{
    const unsigned int base = 10;
    unsigned int len = digit_len(*k);
    unsigned int cbase = 1;
    for (unsigned int i = 0; i < len - 1; i++)
        cbase *= base;
    long long int rev = 0;
    for (unsigned int i = len; i > 0; i--)
    {
        rev += (*k % base) * cbase;
        *k /= base;
        cbase /= base;
    }
    if (rev > INT_MAX)
        return ERR_OVERFLOW;
    *k = rev;
    return OK;
}   


/*
Функция вставляет элемент в массив по индексу.
Принимает на вход int массив, size_t указатель на его длину, int элемент, size_t индекс
*/
void insert(int a[], size_t *a_n, int elem, size_t ind)
{
    if (ind > *a_n)
        ind = *a_n;  // Если указан индекс больше длины, то вставит на последнее место
    for (size_t i = *a_n; i > ind; i--)
        a[i] = a[i - 1];
    a[ind] = elem;
    *a_n += 1;
}


/*
Функция вставляет после положительных элементов их реверсы (со сдвигом остальных).
Получает на вход int массив и size_t его длину
*/
int insert_reversed_pos(int a[], size_t *a_n)
{
    int t;
    int trc;  // Код возврата для передачи кода ошибки наверх по порядку вызовов
    // Проход по массиву в обратном порядке и переписывание всех элементов на add_len правее, при этом 
    for (size_t i = 0; i < *a_n; i++)
    {
        if (a[i] > 0)
        {
            t = a[i];
            if ((trc = reverse_num(&t)) != 0)
                return trc;
            insert(a, a_n, t, i + 1);
            i += 1;
        }
    }
    return OK;
}


int main(void)
{
    int a[DOUBLE_N];
    size_t a_n;
    int rc;
    
    if ((rc = input_array(a, &a_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    if ((rc = insert_reversed_pos(a, &a_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    print_array(a, a_n);
    return OK;
}
