#ifndef LIST__
#define LIST__

#define LIST_OK 0
#define LIST_INVALID_PARAM 1
#define LIST_MEM 2
#define LIST_NOT_FOUND 3
#define LIST_KEY_EXISTS 4

typedef struct key_value_node
{
    char *key;
    int value;
    struct key_value_node *next;
} key_value_node_t;

struct list_type
{
    key_value_node_t *head;
};

typedef struct list_type *list_t;

list_t assoc_list_create(void);

void assoc_list_destroy(list_t arr);

int assoc_list_insert(list_t arr, const char *key, int num);

int assoc_list_find(const list_t arr, const char *key, int **num);

int assoc_list_remove(list_t arr, const char *key);

int assoc_list_clear(list_t arr);

#endif
