#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "data_struct.h"
#include "check_helpers.h"


START_TEST(test_empty_list)
{
    // Вставка в пустой список
    node_t *head = NULL;
    int val = 5;
    node_t *new_node = create_node(&val);

    sorted_insert(&head, new_node, int_comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->data, val);
    ck_assert_ptr_null(head->next);

    free_list(head);
}
END_TEST


START_TEST(test_at_beginning)
{
    // Вставка в начало
    int arr[] = {2, 3, 4};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 1;
    node_t *new_node = create_node(&val);

    sorted_insert(&head, new_node, int_comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->data, val);
    ck_assert_int_eq(*(int*)head->next->data, 2);

    free_list(head);
}
END_TEST


START_TEST(test_in_middle)
{
    // Вставка в середину
    int arr[] = {1, 3, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 4;
    node_t *new_node = create_node(&val);

    sorted_insert(&head, new_node, int_comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->next->next->data, val);
    ck_assert_int_eq(*(int*)head->next->next->next->data, 5);

    free_list(head);
}
END_TEST


START_TEST(test_at_end)
{
    // Вставка в конец
    int arr[] = {1, 2, 3};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 4;
    node_t *new_node = create_node(&val);

    sorted_insert(&head, new_node, int_comparator);

    node_t *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    ck_assert_int_eq(*(int*)curr->data, val);
    ck_assert_ptr_null(curr->next);

    free_list(head);
}
END_TEST


START_TEST(test_duplicate)
{
    // Вставка дубликата
    int arr[] = {1, 2, 3};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 2;
    node_t *new_node = create_node(&val);

    sorted_insert(&head, new_node, int_comparator);

    node_t *curr = head;
    int count_twos = 0;
    while (curr != NULL)
    {
        if (*(int*)curr->data == 2)
            count_twos++;
        curr = curr->next;
    }
    ck_assert_int_eq(count_twos, 2);

    free_list(head);
}
END_TEST


Suite *sorted_insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sorted_insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_empty_list);
    tcase_add_test(tc_pos, test_at_beginning);
    tcase_add_test(tc_pos, test_in_middle);
    tcase_add_test(tc_pos, test_at_end);
    tcase_add_test(tc_pos, test_duplicate);
    suite_add_tcase(s, tc_pos);

    return s;
}
