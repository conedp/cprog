#include "get_answer.h"

/*
Функция удаляет элемент массива по индексу.
Принимает на вход int массив, size_t указатель на его длину и size_t индекс
*/
int delete_by_ind(int a[], size_t *a_n, size_t index)
{
    if (index >= *a_n)
        return ERR_RANGE;
    for (size_t i = index + 1; i < *a_n; i++)
        a[i - 1] = a[i];
    *a_n -= 1;
    return OK;
}


/*
Функция удаляет столбец матрицы по индексу.
Принимает на вход int матрицу, size_t её длину, size_t указатель на её ширину и size_t индекс
*/
int delete_column(int m[][M], size_t m_n, size_t *m_m, size_t index)
{
    int rc;
    size_t wide;
    if (index >= *m_m)
        return ERR_RANGE;
    for (size_t i = 0; i < m_n; i++)
    {
        wide = *m_m;
        if ((rc = delete_by_ind(m[i], &wide, index)) != OK)
            return rc;
    }
    *m_m -= 1;
    return OK;
}


/*
Функция определяет, есть ли цифра в числе.
Принимает на вход int цифру и int число.
*/
bool is_digit_in_num(int digit, int num)
{
    const int base = 10;
    if (num == INT_MIN)
    {
        if (digit == INT_MAX % base + 1)
            return true;
        num /= base;
    }
    num = abs(num);
    
    if (num == 0 && digit == 0)
        return true;
    
    while (num > 0)
    {
        if (num % base == digit)
            return true;
        num /= base;
    }
    return false;
}


/*
Функция определяет, если ли цифра хотя бы в одном числе в столбце матрицы с индексом.
Принимает на вход int матрицу, size_t её длину, size_t её ширину, size_t индекс столбца и int цифру.
Если принимаемый индекс не принадлежит матрице, то вернёт false.
*/
bool is_digit_in_column(int m[][M], size_t m_n, size_t m_m, size_t index, int digit)
{
    bool digit_in_column = false;
    if (index >= m_m)
        return false;
    for (size_t i = 0; i < m_n && !digit_in_column; i++)
        if (is_digit_in_num(digit, m[i][index]))
            digit_in_column = true;
    return digit_in_column;
}


/*
Функция удаляет из матрицы те столбцы, в которых хотя бы в одном числе встретилась цифра.
Принимает на вход int матрицу, size_t её длину, size_t указатель на её ширину и int цифру
*/
int delete_columns_if_digit_in_num(int m[][M], size_t m_n, size_t *m_m, int digit)
{
    int rc;
    for (size_t j = 0; j < *m_m; j++)
    {
        if (is_digit_in_column(m, m_n, *m_m, j, digit))
        {
            if ((rc = delete_column(m, m_n, m_m, j)) != OK)
                return rc;
            j--;
        }
    }
    return OK;
}

