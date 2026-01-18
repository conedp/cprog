#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "check_helpers.h"
#include "list.h"


START_TEST(test_delete_excess_spaces_positive_multiple_spaces)
{
    // Несколько раз по нескколько пробелов
    node_t *head = fill_list_from_string("Hello   World  test");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string("Hello World test");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_delete_excess_spaces_positive_leading_trailing_spaces)
{
    // Пробелы в начале и конце строки
    node_t *head = fill_list_from_string("   Hello World   ");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string(" Hello World ");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_delete_excess_spaces_positive_only_spaces)
{
    // Только пробелы
    node_t *head = fill_list_from_string("     ");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string(" ");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_delete_excess_spaces_positive_no_spaces)
{
    // Нет пробелов
    node_t *head = fill_list_from_string("HelloWorld");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string("HelloWorld");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_delete_excess_spaces_positive_single_spaces)
{
    // Только одиночные пробелы
    node_t *head = fill_list_from_string("Hello World test");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string("Hello World test");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


START_TEST(test_delete_excess_spaces_positive_empty_string)
{
    // Пустая строка
    node_t *head = fill_list_from_string("");

    delete_excess_spaces(head);

    node_t *expected_head = fill_list_from_string("");

    ck_assert_int_eq(compare_lists(head, expected_head), 0);

    free_list(head);
    free_list(expected_head);
}
END_TEST


Suite *delete_excess_spaces_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("delete_excess_spaces");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_multiple_spaces);
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_leading_trailing_spaces);
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_only_spaces);
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_no_spaces);
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_single_spaces);
    tcase_add_test(tc_pos, test_delete_excess_spaces_positive_empty_string);
    suite_add_tcase(s, tc_pos);

    return s;
}
