 /*
Найти и вывести на экран количество уникальных элементов в массиве.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10


/*
Функция печатает в stdin её описание.
Ппринимает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == ERR_IO)
        puts("Input error");
    else if (rc == ERR_RANGE)
        puts("Range error");
    else
        printf("Unknown error %d\n", rc);
}


/*
Функция считывает массив из stdin.
Принимает на вход int указатели на начало массива и на элемент сразу за ним
*/
int input_array(int * const b, int **e)
{
    size_t a_n;
    printf("Input length of array: ");
    if (scanf("%zu", &a_n) != 1)
        return ERR_IO;
    if (a_n == 0 || a_n > N)
        return ERR_RANGE;
    *e = b + a_n;
    int *pc = b;
    printf("Input array: ");
    while (pc < *e)
    {
        if (scanf("%d", pc) != 1)
            return ERR_IO;
        pc += 1;
    }
    return OK;
}


/*
Функция получает на вход int указатели на начало массива и на элемент сразу за ним и int число.
Проверяет, входит ли число в массив
*/
bool is_in_arr(int const * const b, int const *e, int elem)
{
    for (int const *pa = b; pa != e; pa += 1)
        if (elem == *pa)
            return true;
    return false;
}


/*
Функция считает количество уникальных элементов.
Принимает на вход int указатели на начало массива и на элемент сразу за ним для оригинального массива и
для массива уникальных элементов
*/
int count_uniq(int const * const b, int const *e)
{
    size_t counter = 0;
    for (int const *pa = b; pa != e; pa += 1)
        if (! is_in_arr(pa + 1, e, *pa))
            counter += 1;
    return counter;
}


int main(void)
{
    int arr[N];
    int * const b = arr;
    int *e = arr;
    int rc, uniq_n;
    
    if ((rc = input_array(b, &e)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    uniq_n = count_uniq(b, e);
    
    printf("Number of unique elements: %d\n", uniq_n);
    return OK;
}
