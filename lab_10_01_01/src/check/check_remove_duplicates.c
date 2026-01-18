#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "data_struct.h"
#include "check_helpers.h"


START_TEST(test_empty_list)
{
    node_t *head = NULL;

    remove_duplicates(&head, int_comparator);

    ck_assert_ptr_null(head);
}
END_TEST


START_TEST(test_no_duplicates)
{
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    node_t *original_head = fill_list_from_array(arr, sizeof(int), 5);

    remove_duplicates(&head, int_comparator);

    ck_assert_int_eq(compare_lists(head, original_head, int_comparator), 1);

    free_list(head);
    free_list(original_head);
}
END_TEST


START_TEST(test_consecutive)
{
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5};
    int expected_arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 8);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 5);

    remove_duplicates(&head, int_comparator);

    ck_assert_int_eq(compare_lists(head, expected_head, int_comparator), 1);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_non_consecutive)
{
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 4};
    int expected_arr[] = {1, 2, 3, 4, 5};
    node_t *head = fill_list_from_array(arr, sizeof(int), 8);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 5);

    remove_duplicates(&head, int_comparator);

    ck_assert_int_eq(compare_lists(head, expected_head, int_comparator), 1);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_remove_all_duplicates)
{
    int arr[] = {2, 2, 2, 2, 2};
    int expected_arr[] = {2};
    node_t *head = fill_list_from_array(arr, sizeof(int), 5);
    node_t *expected_head = fill_list_from_array(expected_arr, sizeof(int), 1);

    remove_duplicates(&head, int_comparator);

    ck_assert_int_eq(compare_lists(head, expected_head, int_comparator), 1);

    free_list(head);
    free_list(expected_head);
}
END_TEST


Suite *remove_duplicates_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("remove_duplicates");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_empty_list);
    tcase_add_test(tc_pos, test_no_duplicates);
    tcase_add_test(tc_pos, test_consecutive);
    tcase_add_test(tc_pos, test_non_consecutive);
    tcase_add_test(tc_pos, test_remove_all_duplicates);
    suite_add_tcase(s, tc_pos);

    return s;
}
