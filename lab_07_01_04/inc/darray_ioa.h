#ifndef DARRAY_IOA__
#define DARRAY_IOA__

#include <stddef.h>
#include <stdio.h>

int *da_alloc(size_t n, size_t size);

int da_fread(int **data, int **data_end, char *file_name);

int da_fprint(const int *pbeg, const int *pend, FILE *f);

int da_fprint_ex(const int *pbeg, const int *pend, char *file_name);

#endif
