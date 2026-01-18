#include "get_answer.h"


/*
Функция выполняет операцию присваивания для массива.
Принимает на вход int массив-присваиваемое, int массив-присваиватель, size_t их длину
*/
void array_copy(const int src[], int dst[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        dst[i] = src[i];
}


/*
Функция возвращает наименьший элемент массива.
Принимает на вход int массив, size_t его длину
*/
int array_min(const int a[], size_t a_n)
{
    int min = a[0];
    for (size_t i = 1; i < a_n; i++)
        if (a[i] < min)
            min = a[i];
    return min;
}


/*
Функция сравнивает два массива и возвращает -1, если наименьший элемент первого 
массива меньше наименьшего элемента второго массива,
+1, если наоборот и 0, если наименьшие элементы массивов равны.
Принимает на вход int непустой массив (первый), size_t его длину, int непустой массив (второй), size_t его длину
*/
int key(const int a1[], size_t a1_n, const int a2[], size_t a2_n)
{
    int min1 = array_min(a1, a1_n), min2 = array_min(a2, a2_n);
    
    if (min1 < min2)
        return -1;
    else if (min1 == min2)
        return 0;
    else
        return 1;
}


/*
Функция получает на вход непустую int матрицу, size_t её длину и size_t её ширину.
Сортирует матрицу построчно по ключу key(), используя сортировку вставками
*/
int insertion_sort(int m[][M], size_t m_n, size_t m_m)
{
    if (m_n == 1)
        return OK;
    size_t j;
    int t[N];
    for (size_t i = 1; i < m_n; i++)
    {
        array_copy(m[i], t, m_m);
        j = i - 1;
        while (j < N && key(t, m_m, m[j], m_m) == 1)
        {
            array_copy(m[j], m[j + 1], m_m);
            j--;
        }
        array_copy(t, m[j + 1], m_m);
    }
    return OK;
}

