#include <stdlib.h>
#include "errors.h"
#include "check_swap_uni.h"


// Определению перенесено полностью, потому что в программе функция тоже имеет модификатор static
static void swap_uni(void *l, void *r, size_t size)
{
    char tmp;
    char *pl = (char*) l;
    char *pr = (char*) r;

    for (size_t i = 0; i < size; i++)
    {
        tmp = *(pl + i);
        *(pl + i) = *(pr + i);
        *(pr + i) = tmp;
    }
}


START_TEST(test_swap_one_byte)
{
    char a[] = {0, 1};
    size_t size = sizeof(char);

    // Обмен 1 байта

    swap_uni(&a[0], &a[1], size);

    ck_assert_int_eq(a[0], 1);
    ck_assert_int_eq(a[1], 0);
}
END_TEST



START_TEST(test_swap_several_bytes)
{
    double a[] = {0.0, 1.0};
    size_t size = sizeof(double);

    // Обмен нескольких байт

    swap_uni(&a[0], &a[1], size);

    ck_assert_int_eq(a[0], 1);
    ck_assert_int_eq(a[1], 0);
}
END_TEST



START_TEST(test_swap_zero_size)
{
    char a[] = {0, 1};
    size_t size = 0;

    // Обмен нуля байт (ничего не делает)

    swap_uni(&a[0], &a[1], size);

    ck_assert_int_eq(a[0], 0);
    ck_assert_int_eq(a[1], 1);
}
END_TEST


START_TEST(test_swap_intersected_areas)
{
    int a[] = {0, 1, 2, 3};
    size_t size = 2 * sizeof(int);

    // Обмен пересекающихся областей

    swap_uni(&a[0], &a[1], size);

    ck_assert_int_eq(a[0], 1);
    ck_assert_int_eq(a[1], 0);
}
END_TEST


Suite* swap_uni_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("swap_uni");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_swap_one_byte);
    tcase_add_test(tc_pos, test_swap_several_bytes);
    tcase_add_test(tc_pos, test_swap_zero_size);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_swap_intersected_areas);
    suite_add_tcase(s, tc_neg);

    return s;
}

