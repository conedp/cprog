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
Функция считывает квадратную матрицу из stdin.
Принимает на вход int матрицу и size_t указатель на её длину
*/
int input_square_matrix(int m[][M], size_t *m_n)
{
    size_t m_m;
    int rc;
    if ((rc = input_matrix(m, m_n, &m_m)) != OK)
        return rc;
    if (*m_n != m_m)
        return ERR_NOT_SQUARE_MATRIX;
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
Функция печатает матрицу в stdout по строкам через пробел.
Принимает на вход int матрицу, size_t её длину и size_t её ширину
*/
void print_matrix(int m[][N], size_t m_n)
{
    printf("Matrix:\n");
    for (size_t i = 0; i < m_n; i++)
    {
        for (size_t j = 0; j < m_n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}
