#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include <stddef.h>
#include "constants.h"
#include "errors.h"

void array_copy(const int src[], int dst[], size_t n);

int array_min(const int a[], size_t a_n);

int key(const int a1[], size_t a1_n, const int a2[], size_t a2_n);

int insertion_sort(int m[][M], size_t m_n, size_t m_m);

#endif
