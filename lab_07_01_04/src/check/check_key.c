#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "darray_op.h"
#include "check_key.h"


START_TEST(test_two_items)
{
    int a[] = {1, 2};
    int *pbeg, *pend;
    size_t n = sizeof(a) / sizeof(a[0]);
    int rc;

    // Два различных элемента

    rc = key(a, a + n, &pbeg, &pend);

    ck_assert(pend - pbeg == 1);
    ck_assert(*pbeg == 2);
    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_several)
{
    int a[] = {1, 2, 4, 5};
    int *pbeg, *pend;
    size_t n = sizeof(a) / sizeof(a[0]);
    int rc;

    // Два различных элемента

    rc = key(a, a + n, &pbeg, &pend);

    ck_assert(pend - pbeg == 2);
    ck_assert(*pbeg == 4 && *(pbeg + 1) == 5);
    ck_assert_int_eq(rc, OK);
}
END_TEST


START_TEST(test_one_item)
{
    int a[] = {1};
    int *pbeg, *pend;
    size_t n = sizeof(a) / sizeof(a[0]);
    int rc;

    // Один элемент

    rc = key(a, a + n, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST


START_TEST(test_several_equal)
{
    int a[] = {0, 0, 0, 0, 0, 0};
    int *pbeg, *pend;
    size_t n = sizeof(a) / sizeof(a[0]);
    int rc;

    // Несколько одинаковых элементов

    rc = key(a, a + n, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_RANGE);
}
END_TEST


START_TEST(test_zero_items)
{
    int a[] = {0};
    int *pbeg, *pend;
    size_t n = 0;
    int rc;

    // Ноль элементов

    rc = key(a, a + n, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_DATA);
}
END_TEST


START_TEST(test_wrong_pointers_size)
{
    int a[] = {1, 2, 3};
    int *pbeg, *pend;
    int *pcursed = (int*)(((char*) &a[1]) + 2);
    int rc;

    // Некорректные данные - размер области не кратен размеру одного элемента

    rc = key(a, pcursed, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_DATA);
}
END_TEST


START_TEST(test_wrong_pointers_order)
{
    int a[] = {1, 2};
    int *pbeg, *pend;
    size_t n = sizeof(a) / sizeof(a[0]);
    int rc;

    // Некорректные данные - указатель на начало больше чем указатель на конец

    rc = key(a + n, a, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_DATA);
}
END_TEST


START_TEST(test_wrong_pointers_null)
{
    int a[] = {1, 2};
    int *pbeg, *pend;
    int rc;

    // Некорректные данные - есть нулевой указатель

    rc = key(a, NULL, &pbeg, &pend);

    ck_assert_int_eq(rc, ERR_DATA);
}
END_TEST


Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("key");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_two_items);
    tcase_add_test(tc_pos, test_several);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_one_item);
    tcase_add_test(tc_neg, test_several_equal);
    tcase_add_test(tc_neg, test_zero_items);
    tcase_add_test(tc_neg, test_wrong_pointers_size);
    tcase_add_test(tc_neg, test_wrong_pointers_order);
    tcase_add_test(tc_neg, test_wrong_pointers_null);
    suite_add_tcase(s, tc_neg);

    return s;
}
