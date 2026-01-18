#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "associative_array.h"
#include "check_assoc_array_each.h"


static void action_sum(const char *key, int *num, void *param)
{
    (const void) key;
    int *sum = (int*) param;
    *sum += *num;
}


static void action_mult(const char *key, int *num, void *param)
{
    (const void) key;
    int *sum = (int*) param;
    *sum *= *num;
}


START_TEST(tc_pos_each_sum)
{
    // Сумма значений непустого массива
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    int sum = 0;
    assoc_array_error_t err = assoc_array_each(arr, action_sum, &sum);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(sum, 60);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_pos_each_mult)
{
    // Произведение значений непустого массива
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 2);
    assoc_array_insert(arr, "key2", 4);
    assoc_array_insert(arr, "key3", 6);

    int m = 1;
    assoc_array_error_t err = assoc_array_each(arr, action_mult, &m);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(m, 48);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_pos_each_empty)
{
    // Сумма значений пустого массива
    assoc_array_t arr = assoc_array_create();

    int sum = 0;
    assoc_array_error_t err = assoc_array_each(arr, action_sum, &sum);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(sum, 0);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_each_null_array)
{
    // arr == NULL
    int sum = 0;

    assoc_array_error_t err = assoc_array_each(NULL, action_sum, &sum);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


START_TEST(tc_neg_each_null_action)
{
    // action == NULL
    assoc_array_t arr = assoc_array_create();

    int sum = 0;

    assoc_array_error_t err = assoc_array_each(arr, NULL, &sum);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *assoc_array_each_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_each");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_each_sum);
    tcase_add_test(tc_pos, tc_pos_each_mult);
    tcase_add_test(tc_pos, tc_pos_each_empty);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_each_null_array);
    tcase_add_test(tc_neg, tc_neg_each_null_action);
    suite_add_tcase(s, tc_neg);

    return s;
}

