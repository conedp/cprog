#ifndef GET_ANSWER_H
#define GET_ANSWER_H

#include <string.h>
#include <stdbool.h>
#include "constants.h"

int parse_string(char *str, char words[][WORD_LEN], size_t *words_n);

bool is_char_in_arr(char sym, const char word[], size_t word_n);

int delete_by_ind(char word[], size_t *word_n, size_t index);

char *delete_duplicates(char word[], size_t *word_n);

int fill_string(char *dst, char words[][WORD_LEN], size_t words_n);

#endif
