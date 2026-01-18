#include "get_answer.h"

/*
Функция определяет сумма цифр числа.
Принимает на вход int число
*/
int digit_sum(int num)
{
    int sum = 0;
    const int base = 10;
    if (num == INT_MIN)
    {
        num = INT_MAX;
        sum = 1;
    }
    num = abs(num);
    while (num > 0)
    {
        sum += num % base;
        num /= base;
    }
    return sum;
}


/*
Функция циклически сдвигает массив влево на 1 элемент.
Принимает на вход непустой int массив и size_t его длину
*/
void move_left(int a[], size_t a_n)
{
    int t = a[0];
    for (size_t i = 0; i < a_n - 1; i++)
        a[i] = a[i + 1];
    a[a_n - 1] = t;
}


/*
Функция циклически сдвигает элементы массива влево на указанное число позиций.
Принимает на вход непустой int массив, size_t его длину и size_t число позиций для сдвига
*/
void move_left_by(int a[], size_t a_n, size_t move_by)
{
    for (size_t i = 0; i < move_by; i++)
        move_left(a, a_n);
}


/*
Функция заполняет массив элементами матрицы, сумма цифр которых больше 10.
Принимает на вход int матрицу, size_t её длину, size_t её ширину, int массив, size_t указатель на его длину
*/
void fill_array(int m[][M], size_t m_n, size_t m_m, int a[], size_t *a_n)
{
    size_t curr_ind = 0;
    for (size_t i = 0; i < m_n; i++)
        for (size_t j = 0; j < m_m; j++)
        {
            if (digit_sum(m[i][j]) > BORDER)
            {
                a[curr_ind] = m[i][j];
                curr_ind += 1;
            }
        }
    *a_n = curr_ind;
}


/*
Функция перезаписывает элементы матрицы, сумма цифр которых больше 10, по порядку из непустого массива.
Принимает на вход int матрицу, size_t её длину, size_t её ширину, int массив и size_t его длину
*/
int return_to_matrix(int m[][M], size_t m_n, size_t m_m, int a[], size_t a_n)
{
    size_t curr_ind = 0;
    for (size_t i = 0; i < m_n && curr_ind < a_n; i++)
        for (size_t j = 0; j < m_m && curr_ind < a_n; j++)
        {
            if (digit_sum(m[i][j]) > BORDER)
            {
                if (curr_ind >= a_n)
                    return ERR_RANGE;
                m[i][j] = a[curr_ind];
                curr_ind += 1;
            }
        }
    if (curr_ind < a_n)
        return ERR_RANGE;
    return OK;
}


/*
Функция сдвигает элементы матрицы, сумма цифр которых больше 10, влево на 3 позиции.
Принимает на вход int матрицу, size_t её длину, size_t её ширину, int массив, size_t указатель на его длину
*/
int move_suitable_left_by_three(int m[][M], size_t m_n, size_t m_m)
{
    int a[LINE_N];
    size_t a_n;
    int rc;
    fill_array(m, m_n, m_m, a, &a_n);
    if (a_n == 0)
        return ERR_NO_SUITABLE;
    move_left_by(a, a_n, MOVE_LEFT_BY);
    if ((rc = return_to_matrix(m, m_n, m_m, a, a_n)) != OK)
        return rc;
    return OK;
}










