#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include "constants.h"
#include <string.h>

void get_next_word(char *str, char **pbeg, char **pend);

int copy_word(const char *pbeg, const char *pend, char *word, size_t word_size);

int parse_string(char *str, char words[][WORD_LEN], size_t *words_n);

size_t count_str_in_arr(const char *str, char words[][WORD_LEN], size_t words_n);

void form_array(char words_1_src[][WORD_LEN], size_t words_1_src_n, char words_2_src[][WORD_LEN], size_t words_2_src_n, char words_dst[][WORD_LEN], size_t *words_dst_n);

#endif
