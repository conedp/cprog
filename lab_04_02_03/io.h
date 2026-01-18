#ifndef IO_H
#define IO_H

#include "constants.h"
#include <string.h>

int get_line(char *buf, size_t buf_size);

void print_word_array(char words[][WORD_LEN], size_t words_n);

#endif
