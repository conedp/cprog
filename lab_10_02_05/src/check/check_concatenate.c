#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "check_helpers.h"
#include "list.h"


START_TEST(test_concatenate_positive_non_empty)
{
    // Сложение двух непустых строк
    node_t *head1 = fill_list_from_string("Hello");
    node_t *head2 = fill_list_from_string("World");

    concatenate(&head1, head2);

    node_t *expected_head = fill_list_from_string("HelloWorld");

    ck_assert_int_eq(compare_lists(head1, expected_head), 0);

    free_list(head1);
    free_list(head2);
    free_list(expected_head);
}
END_TEST


START_TEST(test_concatenate_positive_empty_to_non_empty)
{
    // Сложение непустой и пустой строк
    node_t *head1 = fill_list_from_string("Hello");
    node_t *head2 = fill_list_from_string("");

    concatenate(&head1, head2);

    node_t *expected_head = fill_list_from_string("Hello");

    ck_assert_int_eq(compare_lists(head1, expected_head), 0);

    free_list(head1);
    free_list(head2);
    free_list(expected_head);
}
END_TEST


START_TEST(test_concatenate_positive_non_empty_to_empty)
{
    // Сложение пустой и непустой строк
    node_t *head1 = fill_list_from_string("");
    node_t *head2 = fill_list_from_string("World");

    concatenate(&head1, head2);

    node_t *expected_head = fill_list_from_string("World");

    ck_assert_int_eq(compare_lists(head1, expected_head), 0);

    free_list(head1);
    free_list(head2);
    free_list(expected_head);
}
END_TEST


START_TEST(test_concatenate_positive_empty_to_empty)
{
    // Сложение двух пустых строк
    node_t *head1 = fill_list_from_string("");
    node_t *head2 = fill_list_from_string("");

    concatenate(&head1, head2);

    node_t *expected_head = fill_list_from_string("");

    ck_assert_int_eq(compare_lists(head1, expected_head), 0);

    free_list(head1);
    free_list(head2);
    free_list(expected_head);
}
END_TEST


START_TEST(test_concatenate_positive_head2_null)
{
    // head_2 == NULL
    node_t *head1 = fill_list_from_string("Hello");

    int result = concatenate(&head1, NULL);

    ck_assert_int_eq(result, 0);

    node_t *expected_head = fill_list_from_string("Hello");

    ck_assert_int_eq(compare_lists(head1, expected_head), 0);

    free_list(head1);
    free_list(expected_head);
}
END_TEST


Suite *concatenate_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Concatenate");

    tc_pos = tcase_create("Positive");
    tcase_add_test(tc_pos, test_concatenate_positive_non_empty);
    tcase_add_test(tc_pos, test_concatenate_positive_empty_to_non_empty);
    tcase_add_test(tc_pos, test_concatenate_positive_non_empty_to_empty);
    tcase_add_test(tc_pos, test_concatenate_positive_empty_to_empty);
    tcase_add_test(tc_pos, test_concatenate_positive_head2_null);
    suite_add_tcase(s, tc_pos);

    return s;
}
