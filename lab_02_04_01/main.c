/*
Упорядочить массив по возрастанию с помощью сортировки вставками и вывести на экран.
*/
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define TEN_FIRST_TAKEN 100

#define N 10


/*
Функция печатает в stdin её описание.
Принимает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == ERR_IO)
        puts("Input error");
    else
        printf("Unknown error %d\n", rc);
}


/*
Функция считывает массив из stdin.
Принимает на вход int массив и size_t указатель на его длину
*/
int input_array(int a[], size_t *a_n)
{
    int elem;
    *a_n = 0;
    while (*a_n < N && scanf("%d", &elem) == 1)
    {
        a[*a_n] = elem;
        *a_n += 1;
    }
    if (scanf("%d", &elem) == 1)
        return TEN_FIRST_TAKEN;
    if (*a_n == 0)
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
Функция сортирует массив, используя сортировку вставками.
Получает на вход int массив и size_t его длину
*/
int insertion_sort(int a[], size_t a_n)
{
    if (a_n == 1)
        return OK;
    size_t j;
    int t;
    for (size_t i = 1; i < a_n; i++)
    {
        t = a[i];
        j = i - 1;
        while (j < N && t < a[j])
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
    return OK;
}


int main(void)
{
    int a[N];
    size_t a_n;
    int rc;
    
    if ((rc = input_array(a, &a_n)) != OK)
    {
        if (rc != TEN_FIRST_TAKEN)
        {
            print_error(rc);
            return rc;
        }
    }
    
    insertion_sort(a, a_n);
    
    print_array(a, a_n);
    if (rc != TEN_FIRST_TAKEN)
        return OK;
    else
        return rc;
}
