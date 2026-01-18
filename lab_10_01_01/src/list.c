#include "list.h"
#include "errors.h"

#include <stdlib.h>

/*
Функция создаёт список из массива данных (в списке хранятся указатели за данные).
Принимает на вход массив структур данных, размер одной структуры и их количество.
*/
node_t *fill_list_from_array(void *arr, size_t size, size_t n)
{
    if (n == 0)
        return NULL;
    char *pcur = arr;
    node_t *head, *curr, *prev;
    head = create_node(pcur);
    if (!head)
        return NULL;
    pcur += size;
    prev = head;
    for (size_t i = 0; i < n - 1; i++)
    {
        curr = create_node((void*) pcur);
        if (!curr)
        {
            free_list(head);
            return NULL;
        }
        pcur += size;
        prev->next = curr;
        prev = curr;
    }
    return head;
}


/*
Функция освобождает память из-под списка (но не из-под данных).
Принимает на вход указатель на голову списка.
*/
void free_list(node_t *head)
{
    node_t *next;

    while (head)
    {
        next = head->next;
        node_free(head);
        head = next;
    }
}


/*
Функция ищет узел в списке по данным. Возвращает узел в случае успеха и NULL в случае неудачи.
Принимает на вход голову списка, указатель на данные для поиска и функцию-компаратор.
*/
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *curr = head;
    while (curr)
    {
        if (comparator(data, curr->data) == 0)
            return curr;
        curr = curr->next;
    }

    return curr;
}


/*
Функция удаляет все повторения из линейного односвязного списка.
Принимает на вход упорядоченный список и функцию-компаратор.
*/
void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*))
{
    if (*head == NULL)
        return;
    if ((*head)->next == NULL)
        return;

    node_t *prev, *curr, *start = *head;
    while (start && start->next)
    {
        prev = start;
        curr = start->next;
        while (curr)
        {
            if (comparator(start->data, curr->data) == 0)
            {
                prev->next = curr->next;
                node_free(curr);
                curr = prev->next;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        start = start->next;
    }
}


/*
Функция вставляет узел elem перед узлом before в списке *head. Если before == NULL, то вставляет узел в конец списка.
Принимает на вход указатель на голову, вставляемый узел и узел, перед которым тот вставляется.
Если before не принадлежит списку (и не NULl), то не изменяет список.
*/
void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
    {
        *head = elem;
        elem->next = before;
        return;
    }

    node_t *prev = *head;
    while (prev && prev->next != before)
        prev = prev->next;
    if (prev)
    {
        prev->next = elem;
        elem->next = before;
    }
    // else => before не принадлежит списку
}


/*
Функция вставляет узел в отсортированный от меньшего (у головы) к большему список.
В случае когда элемент можно вставить на несколько позиций, вставляет на последнюю.
Принимает на вход указатель на голову списка, узел для вставки и функцию-компаратор.
*/
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (*head == NULL)
    {
        *head = element;
        (*head)->next = NULL;
        return;
    }

    node_t *curr = *head;
    while (curr && comparator(element->data, curr->data) >= 0)
        curr = curr->next;
    insert(head, element, curr);
}


/*
Функция сортирует список от меньшего (у головы) к большему.
Принимает на вход голову списка и функцию-компаратор.
Возвращает новую голову.
*/
node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL, *curr = head, *tmp;
    while (curr)
    {
        tmp = curr->next;
        sorted_insert(&new_head, curr, comparator);
        curr = tmp;
    }
    return new_head;
}






