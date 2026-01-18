#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include "constants.h"
#include "errors.h"


int delete_by_ind(int a[], size_t *a_n, size_t index);

int delete_column(int m[][M], size_t m_n, size_t *m_m, size_t index);

bool is_digit_in_num(int digit, int num);

bool is_digit_in_column(int m[][M], size_t m_n, size_t m_m, size_t index, int digit);

int delete_columns_if_digit_in_num(int m[][M], size_t m_n, size_t *m_m, int digit);

#endif
