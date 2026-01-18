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

    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_ptr_null(sorted_head);
}
END_TEST


START_TEST(test_one_element_list)
{
    // Список из одного элемента
    int arr[] = {1};
    node_t *head = fill_list_from_array(arr, sizeof(int), 1);
    node_t *expected_head = fill_list_from_array(arr, sizeof(int), 1);


    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_int_eq(compare_lists(expected_head, sorted_head, int_comparator), 1);

    free_list(sorted_head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_already_sorted_list)
{
    // Упорядоченный список
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    node_t *expected_head = fill_list_from_array(arr, sizeof(int), 5);

    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_int_eq(compare_lists(expected_head, sorted_head, int_comparator), 1);

    free_list(sorted_head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_reverse_sorted_list)
{
    // Обратно-упорядоченный список
    int arr[] = {5, 4, 3, 2, 1};
    int expected_arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 5);

    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_int_eq(compare_lists(sorted_head, expected_head, int_comparator), 1);

    free_list(expected_head);
    free_list(sorted_head);
}
END_TEST


START_TEST(test_random_order_list)
{
    // Список случайных чисел
    int arr[] = {3, 1, 4, 2, 5};
    int expected_arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 5);

    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_int_eq(compare_lists(sorted_head, expected_head, int_comparator), 1);

    free_list(expected_head);
    free_list(sorted_head);
}
END_TEST


START_TEST(test_list_with_duplicates)
{
    // Список с дубликатами
    int arr[] = {3, 1, 4, 2, 3, 5, 2, 1};
    int expected_arr[] = {1, 1, 2, 2, 3, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 8);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 8);

    node_t *sorted_head = sort(head, int_comparator);

    ck_assert_int_eq(compare_lists(sorted_head, expected_head, int_comparator), 1);

    free_list(expected_head);
    free_list(sorted_head);
}
END_TEST


START_TEST(test_random_order_list_char)
{
    // Список случайных символов
    char arr[] = {3, 1, 4, 2, 5};
    char expected_arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(char), 5);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(char), 5);

    node_t *sorted_head = sort(head, char_comparator);

    ck_assert_int_eq(compare_lists(sorted_head, expected_head, char_comparator), 1);

    free_list(expected_head);
    free_list(sorted_head);
}
END_TEST


Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_empty_list);
    tcase_add_test(tc_pos, test_one_element_list);
    tcase_add_test(tc_pos, test_already_sorted_list);
    tcase_add_test(tc_pos, test_reverse_sorted_list);
    tcase_add_test(tc_pos, test_random_order_list);
    tcase_add_test(tc_pos, test_list_with_duplicates);
    tcase_add_test(tc_pos, test_random_order_list_char);
    suite_add_tcase(s, tc_pos);

    return s;
}
