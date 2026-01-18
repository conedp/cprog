#include <check.h>
#include <stdlib.h>

#include "associative_array.h"
#include "check_assoc_array_find.h"


START_TEST(tc_pos_find_existing)
{
    // Поиск существующего
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int *value;
    assoc_array_error_t err = assoc_array_find(arr, "key1", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 10);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_find_non_existing)
{
    // Поиск несуществующего
    assoc_array_t arr = assoc_array_create();

    int *value = NULL;
    assoc_array_error_t err = assoc_array_find(arr, "key1", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_find_null_array)
{
    // arr == NULL
    int *value;
    assoc_array_error_t err = assoc_array_find(NULL, "key1", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


START_TEST(tc_neg_find_null_key)
{
    // key == NULL
    assoc_array_t arr = assoc_array_create();

    int *value;
    assoc_array_error_t err = assoc_array_find(arr, NULL, &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_find_empty_key)
{
    // key - пустая строка
    assoc_array_t arr = assoc_array_create();

    int *value;
    assoc_array_error_t err = assoc_array_find(arr, "", &value);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(tc_neg_find_null_value_ptr)
{
    // указатель на значение - NULL
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    assoc_array_error_t err = assoc_array_find(arr, "key1", NULL);

    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_find");

    tc_pos = tcase_create("positive");
    tcase_add_test(tc_pos, tc_pos_find_existing);
    suite_add_tcase(s, tc_pos);


    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, tc_neg_find_non_existing);
    tcase_add_test(tc_neg, tc_neg_find_null_array);
    tcase_add_test(tc_neg, tc_neg_find_null_key);
    tcase_add_test(tc_neg, tc_neg_find_empty_key);
    tcase_add_test(tc_neg, tc_neg_find_null_value_ptr);
    suite_add_tcase(s, tc_neg);

    return s;
}
