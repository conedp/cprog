#include <check.h>
#include <stdlib.h>

#include "associative_array.h"
#include "check_assoc_array_min.h"


START_TEST(tc_pos_min_not_empty)
{
    // Поиск минимум в непустом массиве
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key3", 30);

    int *value;

    assoc_array_error_t err = assoc_array_min(arr, &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 10);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_min_empty)
{
    // Поиск минимум в пустом массиве
    assoc_array_t arr = assoc_array_create();

    int *value;

    assoc_array_error_t err = assoc_array_min(arr, &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_min_null_array)
{
    // arr == NULL
    int *value;

    assoc_array_error_t err = assoc_array_min(NULL, &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


START_TEST(tc_neg_min_null_value_ptr)
{
    // value == NULL
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 10);

    assoc_array_error_t err = assoc_array_min(arr, NULL);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *assoc_array_min_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_min");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_min_not_empty);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_min_empty);
    tcase_add_test(tc_neg, tc_neg_min_null_array);
    tcase_add_test(tc_neg, tc_neg_min_null_value_ptr);
    suite_add_tcase(s, tc_neg);

    return s;
}
