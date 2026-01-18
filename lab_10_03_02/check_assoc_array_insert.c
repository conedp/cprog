#include <check.h>
#include <stdlib.h>

#include "associative_array.h"
#include "check_assoc_array_insert.h"


START_TEST(tc_pos_insert_single)
{
    // Вставка одной пары
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err = assoc_array_insert(arr, "key1", 10);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 10);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_pos_insert_multiple)
{
    // Вставка нескольних пар
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err = assoc_array_insert(arr, "key1", 10);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    err = assoc_array_insert(arr, "key2", 20);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    err = assoc_array_insert(arr, "key3", 30);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key2", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 20);

    err = assoc_array_find(arr, "key3", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 30);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_insert_null_array)
{
    // arr == NULL
    assoc_array_error_t err = assoc_array_insert(NULL, "key1", 10);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


START_TEST(tc_neg_insert_null_key)
{
    // key == NULL
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err = assoc_array_insert(arr, NULL, 10);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_insert_empty_key)
{
    // key - пустая строка
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err = assoc_array_insert(arr, "", 10);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_insert_key_exists)
{
    // Вставляемый ключ существует
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err = assoc_array_insert(arr, "key1", 10);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    err = assoc_array_insert(arr, "key1", 20);

    ck_assert_int_eq(err, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_insert");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_insert_single);
    tcase_add_test(tc_pos, tc_pos_insert_multiple);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_insert_null_array);
    tcase_add_test(tc_neg, tc_neg_insert_null_key);
    tcase_add_test(tc_neg, tc_neg_insert_empty_key);
    tcase_add_test(tc_neg, tc_neg_insert_key_exists);
    suite_add_tcase(s, tc_neg);

    return s;
}
