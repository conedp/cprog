#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "errors.h"
#include "node.h"
#include "list.h"
#include "list_io.h"
#include "data_struct.h"
#include "data_io.h"


int main(int argc, char **argv)
{
    int rc = OK;
    bool find_mode;
    storage_item_t to_find = { 0 };
    node_t *found;
    storage_item_t *storage;
    size_t storage_n;

    node_t *list = NULL;

    // Если ./app.exe file_name f to_find
    // то ищет структуру и выводит её или сообщение об отсутствии

    // Если ./app.exe file_name o
    // то сортирует и находит структуры, которые пролежали больше 365 дней (товары подлежат списанию)
    // и выводит их

    if (argc == 4 && strcmp(argv[2], "f") == 0)
    {
        find_mode = true;
    }
    else if (argc == 3 && strcmp(argv[2], "o") == 0)
    {
        find_mode = false;
    }
    else
        return ERR_ARGS;

    // Ввести данные
    rc = data_read_ex(argv[1], &storage_n, &storage);
    if (rc != OK)
        return rc;
    // Заполнить
    list = fill_list_from_array((void*) storage, sizeof(storage_item_t), storage_n);
    if (!list)
    {
        storage_free(storage, storage_n);
        return ERR_MEM;
    }
    // Удалить дубликаты (по имени)
    remove_duplicates(&list, cmp_item_name);

    // Обработка согласно выбранному режиму
    if (find_mode)
    {
        to_find.name = strdup(argv[3]);
        if (!to_find.name)
        {
            storage_free(storage, storage_n);
            free_list(list);
            return ERR_MEM;
        }
        found = find(list, (void*) (&to_find), cmp_item_name);
        if (!found)
            puts("Not found");
        else
            print_storage_item((storage_item_t*) found->data);
    }
    else
    {
        // Отсортировать по дням
        list = sort(list, cmp_item_days_reverse);
        // Вывод информации о товарах, пролежавших на складе больше года
        print_certain(list, is_outdated);
    }
    free(to_find.name);
    free_list(list);
    storage_free(storage, storage_n);
    return OK;
}
