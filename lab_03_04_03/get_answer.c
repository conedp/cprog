#include "get_answer.h"

/*
Функция в квадратной матрице зеркально меняет местами две части "банта".
Принимает на вход int матрицу, size_t её длину
*/
void bow_swap(int m[][N], size_t m_n)
{
    int t;
    for (size_t j = 0; j < m_n / 2; j++)
    {
        for (size_t i = j; i < m_n - j; i++)
        {
            t = m[i][j];
            m[i][j] = m[i][m_n - 1 - j];
            m[i][m_n - 1 - j] = t;
        }
    }
}

