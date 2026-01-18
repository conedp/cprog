#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include <stdbool.h>
#include <stddef.h>
#include "constants.h"
#include "errors.h"


bool is_mono_sequence(const int a[], size_t a_n);

void make_is_mono_seq_array(int m[][M], size_t m_n, size_t m_m, int ans[]);

#endif
