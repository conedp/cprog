#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "data_struct.h"
#include "check_helpers.h"


START_TEST(test_empty_list)
{
    // Пустой список
    node_t *head = NULL;
    int val = 5;
    node_t *found_node = find(head, &val, int_comparator);
    ck_assert_ptr_null(found_node);
}
END_TEST


START_TEST(test_element_exists)
{
    // Искомый элемент существует
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    int search_val = 3;

    node_t *found_node = find(head, &search_val, int_comparator);

    ck_assert_ptr_nonnull(found_node);
    ck_assert_int_eq(*(int*)found_node->data, search_val);

    free_list(head);
}
END_TEST


START_TEST(test_element_not_exists)
{
    // Искомый элемент не существует
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    int search_val = 10;

    node_t *found_node = find(head, &search_val, int_comparator);

    ck_assert_ptr_null(found_node);

    free_list(head);
}
END_TEST


START_TEST(test_first_element)
{
    // Искомый элемент находится на первом месте
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    int search_val = 1;

    node_t *found_node = find(head, &search_val, int_comparator);

    ck_assert_ptr_nonnull(found_node);
    ck_assert_int_eq(*(int*)found_node->data, search_val);

    free_list(head);
}
END_TEST


START_TEST(test_last_element)
{
    // Искомый элемент находится на последнем месте
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    int search_val = 5;

    node_t *found_node = find(head, &search_val, int_comparator);

    ck_assert_ptr_nonnull(found_node);
    ck_assert_int_eq(*(int*)found_node->data, search_val);

    free_list(head);
}
END_TEST


Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("find");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_empty_list);
    tcase_add_test(tc_pos, test_element_exists);
    tcase_add_test(tc_pos, test_element_not_exists);
    tcase_add_test(tc_pos, test_first_element);
    tcase_add_test(tc_pos, test_last_element);
    suite_add_tcase(s, tc_pos);

    return s;
}
