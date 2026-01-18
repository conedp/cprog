#include <check.h>
#include <stdlib.h>

#include "associative_array.h"
#include "check_assoc_array_clear.h"


START_TEST(tc_pos_clear_not_empty)
{
    // Опустошение непустого массива
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);

    assoc_array_error_t err = assoc_array_clear(arr);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);
    err = assoc_array_find(arr, "key2", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_pos_clear_empty)
{
    // Опустошение пустого массива
    assoc_array_t arr = assoc_array_create();

    assoc_array_error_t err = assoc_array_clear(arr);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_clear_null_array)
{
    // arr = NULL
    assoc_array_error_t err = assoc_array_clear(NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


Suite *assoc_array_clear_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_clear");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_clear_not_empty);
    tcase_add_test(tc_pos, tc_pos_clear_empty);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_clear_null_array);
    suite_add_tcase(s, tc_neg);

    return s;
}
