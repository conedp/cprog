#ifndef DARRAY_OP__
#define DARRAY_OP__

#include <stddef.h>

typedef int (*cmp_uni_t)(const void *l, const void *r);

int cmp_uni_int(const void *l, const void *r);

void mysort(void *base, size_t num, size_t size, int (*compare)(const void*, const void*));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif
