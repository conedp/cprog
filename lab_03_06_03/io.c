#include "io.h"

/*
Функция считывает длину массива 0 < length <= N из stdin.
Принимает на вход size_t указатель на число.
*/
int input_len(size_t *length)
{
    size_t width;
    printf("Input length of matrix: ");
    if (scanf("%zu", length) != 1)
        return ERR_IO;
    if (*length == 0 || *length > N)
        return ERR_RANGE;
    printf("Input width of matrix: ");
    if (scanf("%zu", &width) != 1)
        return ERR_IO;
    if (width == 0 || width > N)
        return ERR_RANGE;
    if (width != *length)
        return ERR_NOT_SQUARE_MATRIX;
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
