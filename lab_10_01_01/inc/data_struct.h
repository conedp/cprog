#ifndef DATA_STRUCT__
#define DATA_STRUCT__

typedef struct storage_item
{
    char *name;
    int cost;
    int n_days;  // сколько времени товар лежит на складе
} storage_item_t;

#include <stddef.h>

int cmp_item_name(const void *l, const void *r);

int cmp_item_days_reverse(const void *l, const void *r);

int is_outdated(const void *data);

void print_storage_item(const storage_item_t *item);

void storage_free(storage_item_t *arr, size_t n);

#endif
