#include "get_answer.h"

/*
Функция определяет, является ли последовательность монотонной.
Принимает на вход int массив и size_t его длину.
*/
bool is_mono_sequence(const int a[], size_t a_n)
{
    bool is_dec = true, is_inc = true;
    if (a_n > 1)
    {
        for (size_t i = 0; i < a_n - 1 && (is_dec || is_inc); i++)
        {
            if (a[i + 1] > a[i])
            {
                is_dec = false;
            }
            if (a[i + 1] < a[i])
            {
                is_inc = false;
            }
        }
    }
    else
        is_dec = is_inc = false;
    
    return (is_inc || is_dec);
}


/*
Функция заполняет массив: 1 если соответствующая строка матрицы образует монотонную последовательность, 0 в других случах.
Принимает на вход int матрицу, size_t её длину, size_t её ширину, int массив для заполнения.
*/
void make_is_mono_seq_array(int m[][M], size_t m_n, size_t m_m, int ans[])
{
    for (size_t i = 0; i < m_n; i++)
    {
        if (is_mono_sequence(m[i], m_m))
            ans[i] = 1;
        else
            ans[i] = 0;
    }
}
