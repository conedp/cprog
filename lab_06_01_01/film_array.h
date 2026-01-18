#ifndef FILM_ARRAY__
#define FILM_ARRAY__

#include <stdio.h>
#include <stddef.h>
#include "film.h"
#include "errors.h"

#define N_MAX 15

// Имена для значений переменной sorted_by в main.c
#define TITLE 0
#define NAME 1
#define YEAR 2

typedef int (*cmp_film_t)(const struct film_t *l, const struct film_t *r);

void fa_insert(struct film_t *pfilms, size_t *n, const struct film_t *in_film, size_t ind);

int fa_read_with_sort_by_given(FILE *f, struct film_t *pfilms, size_t n_max, size_t *n, cmp_film_t cmp);

int fa_print(FILE *f, const struct film_t *pfilms, size_t n);

struct film_t *fa_bin_search_by_given(struct film_t *pfilms, size_t n, struct film_t *to_search, cmp_film_t cmp);

#endif
