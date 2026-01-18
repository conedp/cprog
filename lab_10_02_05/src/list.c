#include "list.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/*
Функция создаёт список полудинамических строк из строки.
Принимает на вход строку.
*/
node_t *fill_list_from_string(char *str)
{
    size_t ind = 0, len = strlen(str) + 1;
    node_t *head, *curr, *prev;
    head = create_node(str, ind);
    if (!head)
        return NULL;
    ind += PART_LEN;
    prev = head;
    while (ind < len)
    {
        curr = create_node(str, ind);
        if (!curr)
        {
            free_list(head);
            return NULL;
        }
        ind += PART_LEN;
        prev->next = curr;
        prev = curr;
    }
    return head;
}


/*
Функция освобождает память из-под списка.
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
Функция конкатенирует полудинамические строки. Добавляет вторую строку к первой, изменяет первую.
Принимает на вход головы списков первой и второй строк.
*/
int concatenate(node_t **head_1, node_t *head_2)
{
    node_t *curr1 = *head_1, *curr2 = head_2;
    size_t i1 = 0, i2 = 0;
    bool end = false;

    if (!(*head_1))
    {
        *head_1 = head_2;
        return OK;
    }
    if (!head_2)
        return OK;

    while (curr1->next)
        curr1 = curr1->next;
    while (curr1->s[i1] != 0)
        i1++;
    while (curr2)
    {
        i2 = 0;
        while (i2 < PART_LEN && !end)
        {
            curr1->s[i1] = curr2->s[i2];
            if (curr2->s[i2] == 0)
                end = true;
            else
            {
                i1++;
                if (i1 == PART_LEN)
                {
                    curr1->next = create_node("", 0);
                    if (!curr1->next)
                        return ERR_MEM;
                    i1 = 0;
                    curr1 = curr1->next;
                }
                i2++;
            }
        }
        curr2 = curr2->next;
    }
    return OK;
}


/*
Функция удаляет из полудинамической строки символ, расположенный в узле node по индексу ind.
*/
static int delete_char(node_t *head, node_t *node, size_t ind)
{
    node_t *curr = head, *curr2;
    assert(head);
    assert(node);
    assert(ind < PART_LEN);

    while (curr != node)
        curr = curr->next;
    if (curr == NULL)
        return ERR_NOT_IN_LIST;

    size_t i1 = ind, i2 = ind + 1;
    if (i2 < PART_LEN)
        curr2 = curr;
    else
    {
        i2 = 0;
        curr2 = curr->next;
    }
    while (curr2->s[i2] != 0)
    {
        curr->s[i1] = curr2->s[i2];
        i1++;
        if (i1 == PART_LEN)
        {
            i1 = 0;
            curr = curr->next;
        }
        i2 = i1 + 1;
        if (i2 < PART_LEN)
            curr2 = curr;
        else
        {
            i2 = 0;
            curr2 = curr->next;
        }
    }
    curr->s[i1] = curr2->s[i2];
    i1++;
    if (i1 == PART_LEN)
    {
        i1 = 0;
        curr = curr->next;
    }
    i2 = i1 + 1;
    if (i2 < PART_LEN)
        curr2 = curr;
    else
    {
        i2 = 0;
        curr2 = curr->next;
    }
    return OK;
}


/*
Функция удаляет все стоящие рядом лишние пробелы в полудинамической строке.
*/
int delete_excess_spaces(node_t *head)
{
    assert(head);
    int rc = OK;
    node_t *curr1 = head, *curr2 = head;
    size_t i1 = 0, i2 = i1 + 1;

    if (curr2->s[0] == 0)
        return OK;

    while (curr2 && curr2->s[i2])
    {
        if (curr1->s[i1] == ' ' && curr2->s[i2] == ' ')
        {
            rc = delete_char(head, curr2, i2);
            if (rc != OK)
                return rc;
        }
        else
        {
            i1++;
            if (i1 == PART_LEN)
            {
                i1 = 0;
                curr1 = curr1->next;
            }
            i2 = i1 + 1;
            if (i2 < PART_LEN)
                curr2 = curr1;
            else
            {
                i2 = 0;
                curr2 = curr1->next;
            }
        }
    }
    // Удалить ненужные узлы если такие появились
    curr1 = head;
    i1 = 0;
    while (curr1 && curr1->s[i1])
    {
        i1++;
        if (i1 == PART_LEN)
        {
            i1 = 0;
            curr1 = curr1->next;
        }
    }
    if (!curr1->s[i1] && curr1->next)
    {
        free_list(curr1->next);
        curr1->next = NULL;
    }
    return OK;
}


/*
Функция находит позицию, по которой в полудинамической строке расположена подстрока substr.
*/
int find_substring(node_t *head, char *substr, size_t *pos)
{
    assert(substr);
    assert(head);

    node_t *curr1 = head, *curr2 = head;
    size_t i1 = 0, i2, is = 0, substr_len = strlen(substr), true_ind = i1;
    bool in_substr = false;

    while (curr1 && curr1->s[i1])
    {
        if (curr1->s[i1] == substr[is])
        {
            in_substr = true;
            is++;
            if (is == substr_len)
            {
                *pos = true_ind;
                return OK;
            }
            i2 = i1 + 1;
            if (i2 < PART_LEN)
                curr2 = curr1;
            else
            {
                i2 = 0;
                curr2 = curr1->next;
            }
            while (curr2 && curr2->s[i2] && in_substr)
            {
                if (curr2->s[i2] != substr[is])
                {
                    in_substr = false;
                    is = -1;
                }
                i2++;
                if (i2 == PART_LEN)
                {
                    i2 = 0;
                    curr2 = curr2->next;
                }
                is++;
                if (is == substr_len)
                {
                    *pos = true_ind;
                    return OK;
                }
            }
        }
        i1++;
        true_ind++;
        if (i1 == PART_LEN)
        {
            i1 = 0;
            curr1 = curr1->next;
        }
    }
    return NOT_FOUND;
}


void print_str(node_t *head)
{
    node_t *curr = head;
    size_t i = 0;
    while (curr && curr->s[i])
    {
        printf("%c", curr->s[i]);
        i++;
        if (i == PART_LEN)
        {
            i = 0;
            curr = curr->next;
        }
    }
    printf("\n");
}










