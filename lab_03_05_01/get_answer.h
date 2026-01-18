#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include "errors.h"

int digit_sum(int num);

void move_left(int a[], size_t a_n);

void move_left_by(int a[], size_t a_n, size_t move_by);

void fill_array(int m[][M], size_t m_n, size_t m_m, int a[], size_t *a_n);

int return_to_matrix(int m[][M], size_t m_n, size_t m_m, int a[], size_t a_n);

int move_suitable_left_by_three(int m[][M], size_t m_n, size_t m_m);

#endif
