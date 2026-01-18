#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "darray_op.h"
#include "darray_ioa.h"
#include "errors.h"


/*
Фукнция меняет местами два участка памяти размером size байт.
Принимает на вход указатели на левый и правый элементы и size_t размер. Участки памяти не должны пересекаться
*/
static void swap_uni(void *l, void *r, size_t size)
{
    char tmp;
    char *pl = (char*) l;
    char *pr = (char*) r;

    for (char *curr_l = pl, *curr_r = pr; curr_l < pl + size; curr_l++, curr_r++)
    {
        tmp = *curr_l;
        *curr_l = *curr_r;
        *curr_r = tmp;
    }
}


/*
Функция сравнивает два элемента как целые числа типа int.
Принимает на вход указатель на левый элемент и указатель на правый элемент
*/
int cmp_uni_int(const void *l, const void *r)
{
    const int *pl = l;
    const int *pr = r;
    return *pl - *pr;
}


/*
Функция сортирует массив элементов с помощью двухпроходной сортировки пузырьком с флагом.
Принимает на вход указатель на начало массива, количество элементов в нём, размер одного элемента и указтель на функцию сортировки
*/
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    if (size == 0)
        return;
    char *pbeg = base, *pend = (char*) base + num * size;
    if (pend == pbeg)
        return;
    if (pend - pbeg == (long) size)
        return;

    // plast_up - указатель на последний "всплывший" элемент при прямом проходе, plast_down - при обратном.
    // Эти указатели являются флагом в данной реализации
    char *plast_up = pend, *plast_down = pbeg, *ptmp;

    // ptop и pbot - указатели, отсчитывающие максимальное необходимое количество циклов "всплытия" для прямого и обратного проходов
    for (char *ptop = pend, *pbot = pbeg; ptop > pbeg + size && pbot < pend - size && (plast_down < pend - size * 2 || plast_up > pbeg + size); ptop -= size, pbot += size)
    {
        ptmp = plast_up;
        // pcur и pprev - указатели на текущий и предшествующий ему элементы массива, в случае выполнения условия сравнения, происходит обмен этих элементов
        for (char *pprev = pbeg, *pcur = pbeg + size; pcur < plast_up; pprev = pcur, pcur += size)
            if (compare(pprev, pcur) > 0)
            {
                swap_uni(pprev, pcur, size);
                ptmp = pcur;
            }
        plast_up = ptmp;
        ptmp = plast_down;
        for (char *pcur = pend - size * 2, *pprev = pend - size; pcur >= plast_down; pprev = pcur, pcur -= size)
            if (compare(pcur, pprev) > 0)
            {
                swap_uni(pprev, pcur, size);
                ptmp = pcur;
            }
        plast_down = ptmp;
    }
}


/*
Функция рассчитывает среднее арифметическое в непустом массиве целых чисел.
Принимает на вход указатель на начало массива, указатель за конец массива
*/
static double calc_avg(const int *pbeg, const int *pend)
{
    assert((pend - pbeg) > 0);
    double avg = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        avg += *pcur;
    avg = avg / (pend - pbeg);
    return avg;
}


/*
Функция считает количество элементов массива целых чисел, которые больше некого значения.
Принимает на вход указатель на начало массива, указатель за конец массива, double число
*/
static size_t count_elems_gt(const int *pbeg, const int *pend, double num)
{
    assert((pend - pbeg) > 0);
    size_t counter = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        if (*pcur > num)
            counter += 1;
    return counter;
}


// Перенос отфильтрованных элементов в новый массив
static void move_elems_gt(const int *pb_src, const int *pe_src, double num, int **pb_dst)
{
    assert((pe_src - pb_src) > 0);
    int *pcur_dst = *pb_dst;
    for (const int *pcur_src = pb_src; pcur_src < pe_src; pcur_src++)
        if (*pcur_src > num)
        {
            *pcur_dst = *pcur_src;
            pcur_dst++;
        }
}


/*
Функция создаёт новый динамический массив целых чисел и переносит в него те элементы,
которые больше среднего арифметического всех. Принимает на вход пару указателей на начало и за конец
массива - источника и пару указателей на указатели
*/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    double avg = 0;
    size_t dst_len = 0;

    *pb_dst = NULL;
    *pe_dst = NULL;

    if (pb_src - pe_src == 0)
        return ERR_DATA;
    if (((char*) pb_src - (char*) pe_src) % sizeof(int) != 0)
        return ERR_DATA;
    if (pb_src > pe_src)
        return ERR_DATA;
    if (pb_src == NULL || pe_src == NULL)
        return ERR_DATA;

    // Расчёт среднего арифметического
    avg = calc_avg(pb_src, pe_src);

    // Создание нового массива
    dst_len = count_elems_gt(pb_src, pe_src, avg);
    if (dst_len == 0)
    {
        *pb_dst = NULL;
        *pe_dst = NULL;
    return ERR_RANGE;
    }
    else
    {
        *pb_dst = da_alloc(dst_len, sizeof(int));
        if (!(*pb_dst))
            return ERR_MEM;
        *pe_dst = *pb_dst + dst_len;
    }

    move_elems_gt(pb_src, pe_src, avg, pb_dst);

    return OK;
}
