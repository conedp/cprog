#include <stdlib.h>
#include "errors.h"
#include "darray_ioa.h"
#include "check_da_alloc.h"


START_TEST(test_alloc_one_byte)
{
    size_t n = 1;
    size_t size = 1;
    int *da;
    int rc;

    // Выделение 1 байта памяти

    da = da_alloc(n, size);
    if (!da)
        rc = ERR_MEM;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_alloc_one_item)
{
    size_t n = 1;
    size_t size = 8;
    int *da;
    int rc;

    // Выделение памяти под один элемент массива

    da = da_alloc(n, size);
    if (!da)
        rc = ERR_MEM;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_alloc_several)
{
    size_t n = 8;
    size_t size = 2;
    int *da;
    int rc;

    // Выделение памяти для нескольких элементов массива

    da = da_alloc(n, size);
    if (!da)
        rc = ERR_MEM;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_alloc_zero_items)
{
    size_t n = 0;
    size_t size = 1;
    int *da;
    int rc;

    // Выделение памяти для 0 элементов

    da = da_alloc(n, size);
    if (!da)
        rc = ERR_MEM;

    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_alloc_zero_size)
{
    size_t n = 1;
    size_t size = 0;
    int *da;
    int rc;

    // Выделение памяти для элементов размером 0 байт

    da = da_alloc(n, size);
    if (!da)
        rc = ERR_MEM;

    ck_assert_int_eq(rc, OK);
}
END_TEST


Suite* da_alloc_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("da_alloc");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_alloc_one_byte);
    tcase_add_test(tc_pos, test_alloc_one_item);
    tcase_add_test(tc_pos, test_alloc_several);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_alloc_zero_items);
    tcase_add_test(tc_neg, test_alloc_zero_size);
    suite_add_tcase(s, tc_neg);

    return s;
}
