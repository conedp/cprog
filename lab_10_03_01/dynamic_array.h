#ifndef DYNAMIC_ARRAY__
#define DYNAMIC_ARRAY__

#define INIT_CAPACITY 8
#define RESIZE 2

#define DARRAY_OK 0
#define DARRAY_INVALID_PARAM 1
#define DARRAY_MEM 2
#define DARRAY_NOT_FOUND 3
#define DARRAY_KEY_EXISTS 4


typedef struct key_value_pair
{
    char *key;
    int value;
} key_value_pair_t;


struct dynamic_array_type
{
    key_value_pair_t *pairs;
    size_t size;
    size_t capacity;
};

typedef struct dynamic_array_type *darray_t;


darray_t dyn_array_create(void);

void dyn_array_destroy(darray_t arr);

int resize_array(darray_t arr);

int dyn_array_insert(darray_t arr, const char *key, int num);

int dyn_array_find(const darray_t arr, const char *key, int **num);

int dyn_array_remove(darray_t arr, const char *key);

int dyn_array_clear(darray_t arr);

#endif
