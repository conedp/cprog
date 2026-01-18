#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "errors.h"
#include "darray_op.h"
#include "check_mysort.h"


static int cmp_arr(void *pbeg_l, void *pbeg_r, size_t size, size_t n, int (*cmp)(const void *l, const void *r))
{
    int rc;
    for (char *pcur_l = pbeg_l, *pcur_r = pbeg_r; pcur_l < ((char*) pbeg_l + (size * n)) && pcur_r < ((char*) pbeg_r + (size * n)); pcur_l += size, pcur_r += size)
        if ((rc = cmp(pcur_l, pcur_r)) != 0)
            return rc;
    return 0;
}


START_TEST(test_length_one)
{
    int a[] = {1};
    int b[] = {1};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Массив длины 1

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_length_two_ordered_forward)
{
    int a[] = {1, 2};
    int b[] = {1, 2};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Упорядоченный по возрастанию массив длины 2

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_length_two_ordered_backwards)
{
    int a[] = {2, 1};
    int b[] = {1, 2};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Упорядоченный по убыванию массив длины 2

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_ordered_forward)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Упорядоченный по возрастанию массив

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_unordered_without_duplicates)
{
    int a[] = {3, 1, -8, 5, 6, 7};
    int b[] = {-8, 1, 3, 5, 6, 7};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Неупорядоченный массив без повторений

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_unordered_with_duplicates)
{
    int a[] = {0, -11, 1, 0, 1, 9, 6};
    int b[] = {-11, 0, 0, 1, 1, 6, 9};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Неупорядоченный массив с повторениями

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


START_TEST(test_ordered_backwards_with_duplicates)
{
    int a[] = {10, 9, 9, 8, 7, 7, 3, 1};
    int b[] = {1, 3, 7, 7, 8, 9, 9, 10};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(int);

    // Упорядоченный по убыванию массив с повторениями

    mysort(a, n, size, cmp_uni_int);

    ck_assert(cmp_arr(a, b, sizeof(int), n, cmp_uni_int) == 0);
}
END_TEST


struct elem_t
    {
        int first;
        int second;
    };


static int cmp_uni_double(const void *l, const void *r)
{
    const double *pl = l;
    const double *pr = r;
    const double eps = 10e-8;
    if (fabs(*pr - *pl) < eps)
        return 0;
    else if (*pl < *pr)
        return -1;
    else
        return 1;
}


START_TEST(test_double)
{

    double a[] = {0.1, 0, 0.05, 2, 1.9};
    double b[] = {0, 0.05, 0.1, 1.9, 2};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(struct elem_t);

    // Массив структур (проверка на устойчивость)

    mysort(a, n, size, cmp_uni_double);

    ck_assert(cmp_arr(a, b, sizeof(double), n, cmp_uni_double) == 0);
}
END_TEST


static int cmp_uni_elem(const void *l, const void *r)
{
    const struct elem_t *pl = l;
    const struct elem_t *pr = r;
    return pl->first - pr->first;
}


START_TEST(test_struct)
{

    struct elem_t a[] = {{1, 1}, {1, 2}, {-2, 1}};
    struct elem_t b[] = {{-2, 1}, {1, 1}, {1, 2}};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(struct elem_t);

    // Массив структур (проверка на устойчивость)

    mysort(a, n, size, cmp_uni_elem);

    ck_assert(cmp_arr(a, b, sizeof(struct elem_t), n, cmp_uni_elem) == 0 && a[1].second == 1 && a[2].second == 2);
}
END_TEST


static int strcmp_v(const void *l, const void *r)
{
    const char *pl = l;
    const char *pr = r;
    return strcmp(pl, pr);
}


START_TEST(test_string)
{

    char* a[] = {"abd", "bac", "abc"};
    char* b[] = {"abc", "abd", "bac"};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t size = sizeof(a[0]);

    // Массив строк

    mysort(a, n, size, strcmp_v);

    ck_assert(cmp_arr(a, b, sizeof(a[0]), n, strcmp_v) == 0);
}
END_TEST



Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_length_one);
    tcase_add_test(tc_pos, test_length_two_ordered_forward);
    tcase_add_test(tc_pos, test_length_two_ordered_backwards);
    tcase_add_test(tc_pos, test_ordered_forward);
    tcase_add_test(tc_pos, test_unordered_without_duplicates);
    tcase_add_test(tc_pos, test_unordered_with_duplicates);
    tcase_add_test(tc_pos, test_ordered_backwards_with_duplicates);
    tcase_add_test(tc_pos, test_struct);
    tcase_add_test(tc_pos, test_string);
    tcase_add_test(tc_pos, test_double);
    suite_add_tcase(s, tc_pos);

    return s;
}
