#ifndef DATA_IO__
#define DATA_IO__

#include "data_struct.h"
#include <stddef.h>
#include <stdio.h>

storage_item_t *item_array_alloc(size_t n);

int data_input(FILE *f, size_t n, storage_item_t *arr);

int data_read_ex(char *file_name, size_t *n, storage_item_t **arr);

#endif
