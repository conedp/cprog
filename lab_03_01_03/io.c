#include "io.h"

/*
Функция считывает массив из stdin.
Принимает на вход int массив и size_t его длину
*/
int input_array(int a[], size_t a_n)
{
    for (size_t i = 0; i < a_n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}


/*
Функция считывает матрицу из stdin.
Принимает на вход int матрицу, size_t указатель на её длину и size_t указатель на её ширину
*/
int input_matrix(int m[][M], size_t *m_n, size_t *m_m)
{
    printf("Input length of matrix: ");
    if (scanf("%zu", m_n) != 1)
        return ERR_IO;
    if (*m_n == 0 || *m_n > N)
        return ERR_RANGE;
    printf("Input width of matrix: ");
    if (scanf("%zu", m_m) != 1)
        return ERR_IO;
    if (*m_m == 0 || *m_m > M)
        return ERR_RANGE;
    printf("Input matrix (line by line): \n");
    for (size_t i = 0; i < *m_n; i++)
        if (input_array(m[i], *m_m) != OK)
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
