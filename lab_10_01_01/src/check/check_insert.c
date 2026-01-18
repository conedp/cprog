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
    int val = 10;
    node_t *new_node = create_node(&val);

    insert(&head, new_node, NULL);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->data, val);
    ck_assert_ptr_null(head->next);

    free_list(head);
}
END_TEST


START_TEST(test_at_beginning)
{
    // Вставка перед head (в начало)
    int arr[] = {2, 3, 4};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 1;
    node_t *new_node = create_node(&val);

    insert(&head, new_node, head);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->data, val);
    ck_assert_int_eq(*(int*)head->next->data, 2);

    free_list(head);
}
END_TEST


START_TEST(test_in_middle)
{
    // Вставка в середину
    int arr[] = {1, 3, 4};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    int val = 2;
    node_t *new_node = create_node(&val);
    node_t *before_node = head->next;

    insert(&head, new_node, before_node);

    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(*(int*)head->next->data, val);
    ck_assert_int_eq(*(int*)head->next->next->data, 3);

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

    insert(&head, new_node, NULL);

    node_t *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    ck_assert_int_eq(*(int*)curr->data, val);
    ck_assert_ptr_null(curr->next);

    free_list(head);
}
END_TEST


START_TEST(test_before_not_in_list)
{
    // before не принадлежит списку и не равен NULL
    int arr[] = {1, 2, 3};
    int expected_arr[] = {1, 2, 3};
    node_t *head = fill_list_from_array(arr, sizeof(int), 3);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 3);
    int val = 4;
    node_t *new_node = create_node(&val);

    insert(&head, new_node, (node_t*) 1);

    ck_assert_int_eq(compare_lists(head, expected_head, int_comparator), 1);

    free_list(expected_head);
    free_list(head);
    node_free(new_node);
}
END_TEST


Suite *insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_empty_list);
    tcase_add_test(tc_pos, test_at_beginning);
    tcase_add_test(tc_pos, test_in_middle);
    tcase_add_test(tc_pos, test_at_end);
    tcase_add_test(tc_pos, test_before_not_in_list);
    suite_add_tcase(s, tc_pos);

    return s;
}
