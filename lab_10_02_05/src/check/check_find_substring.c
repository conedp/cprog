#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "check_helpers.h"
#include "list.h"


START_TEST(test_find_substring_positive_beginning)
{
    // Подстрока в начале
    node_t *head = fill_list_from_string("HelloWorld");
    size_t pos;

    int result = find_substring(head, "Hello", &pos);

    ck_assert_int_eq(result, 0);
    ck_assert_uint_eq(pos, 0);

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_positive_middle)
{
    // Подстрока посередине
    node_t *head = fill_list_from_string("HelloWorldTest");
    size_t pos;

    int result = find_substring(head, "World", &pos);

    ck_assert_int_eq(result, 0);
    ck_assert_uint_eq(pos, 5);

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_positive_end)
{
    // Подстрока в конце
    node_t *head = fill_list_from_string("HelloWorld");
    size_t pos;

    int result = find_substring(head, "World", &pos);

    ck_assert_int_eq(result, 0);
    ck_assert_uint_eq(pos, 5);

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_positive_whole_string)
{
    // Подстрока равна всей строке
    node_t *head = fill_list_from_string("HelloWorld");
    size_t pos;

    int result = find_substring(head, "HelloWorld", &pos);

    ck_assert_int_eq(result, 0);
    ck_assert_uint_eq(pos, 0);

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_positive_empty_substring)
{
    // Пустая подстрока
    node_t *head = fill_list_from_string("HelloWorld");
    size_t pos;

    int result = find_substring(head, "", &pos);

    ck_assert_int_eq(result, 100);  // NOT_FOUND == 100

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_positive_multiple_occurrences_first)
{
    // Несколько вхождений подстроки
    node_t *head = fill_list_from_string("abababa");
    size_t pos;

    int result = find_substring(head, "aba", &pos);

    ck_assert_int_eq(result, 0);
    ck_assert_uint_eq(pos, 0);

    free_list(head);
}
END_TEST


START_TEST(test_find_substring_negative_not_found)
{
    // Подстрока не входит
    node_t *head = fill_list_from_string("HelloWorld");
    size_t pos;

    int result = find_substring(head, "Goodbye", &pos);

    ck_assert_int_ne(result, 0);

    free_list(head);
}
END_TEST


Suite *find_substring_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("find_substring");

    tc_pos = tcase_create("Positive");
    tcase_add_test(tc_pos, test_find_substring_positive_beginning);
    tcase_add_test(tc_pos, test_find_substring_positive_middle);
    tcase_add_test(tc_pos, test_find_substring_positive_end);
    tcase_add_test(tc_pos, test_find_substring_positive_whole_string);
    tcase_add_test(tc_pos, test_find_substring_positive_empty_substring);
    tcase_add_test(tc_pos, test_find_substring_positive_multiple_occurrences_first);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Negative");
    tcase_add_test(tc_neg, test_find_substring_negative_not_found);
    suite_add_tcase(s, tc_neg);

    return s;
}
