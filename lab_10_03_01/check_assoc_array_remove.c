#include <check.h>
#include <stdlib.h>

#include "associative_array.h"
#include "check_assoc_array_remove.h"


START_TEST(tc_pos_remove_existing)
{
    // Удаление существующего
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    assoc_array_error_t err = assoc_array_remove(arr, "key1");

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_pos_remove_existing_and_double_destroy)
{
    // Удаление существующего
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    assoc_array_error_t err = assoc_array_remove(arr, "key1");

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_remove_non_existing)
{
    // Удаление несуществующего
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_remove(arr, "key1");

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_remove_null_array)
{
    // arr == NULL
    assoc_array_error_t err = assoc_array_remove(NULL, "key1");

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


START_TEST(tc_neg_remove_null_key)
{
    // key== NULL
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_remove(arr, NULL);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_remove_empty_key)
{
    // key - пустая строка
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_remove(arr, "");

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_remove");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_remove_existing);
    tcase_add_test(tc_pos, tc_pos_remove_existing_and_double_destroy);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_remove_non_existing);
    tcase_add_test(tc_neg, tc_neg_remove_null_array);
    tcase_add_test(tc_neg, tc_neg_remove_null_key);
    tcase_add_test(tc_neg, tc_neg_remove_empty_key);
    suite_add_tcase(s, tc_neg);

    return s;
}
