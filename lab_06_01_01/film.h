#ifndef FILM__
#define FILM__

#include <stdio.h>
#include "errors.h"

#define TITLE_LEN 25
#define NAME_LEN 25

#define IN_TITLE_LEN (TITLE_LEN + 2)
#define IN_NAME_LEN (NAME_LEN + 2)

struct film_t
{
    char title[TITLE_LEN + 1];
    char name[NAME_LEN + 1];
    int year;
};

int film_read(FILE *f, struct film_t *pfilm);

int film_print(FILE *f, const struct film_t *pfilm);

int film_cpy(const struct film_t *dst, const struct film_t *src);

int film_cmp_by_title(const struct film_t *l, const struct film_t *r);

int film_cmp_by_name(const struct film_t *l, const struct film_t *r);

int film_cmp_by_year(const struct film_t *l, const struct film_t *r);

#endif
