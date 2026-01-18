#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "constants.h"
#include "errors.h"

int input_array(int a[], size_t a_n);

int input_square_matrix(int m[][M], size_t *m_n);

int input_matrix(int m[][M], size_t *m_n, size_t *m_m);

void print_matrix(int m[][N], size_t m_n);

#endif
