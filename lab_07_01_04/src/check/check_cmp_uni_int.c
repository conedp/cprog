#include <stdlib.h>
#include "errors.h"
#include "darray_op.h"
#include "check_cmp_uni_int.h"


START_TEST(test_l_lt_r)
{
    int l = 0, r = 1, ans;

    // Левое меньше правого

    ans = cmp_uni_int(&l, &r);

    ck_assert(ans < 0);
}
END_TEST


START_TEST(test_l_gt_r)
{
    int l = 1, r = -2, ans;

    // Правое меньше левого

    ans = cmp_uni_int(&l, &r);

    ck_assert(ans > 0);
}
END_TEST


START_TEST(test_l_eq_r)
{
    int l = 0, r = 0, ans;

    // Равенство

    ans = cmp_uni_int(&l, &r);

    ck_assert(ans == 0);
}
END_TEST


Suite* cmp_uni_int_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("cmp_uni_int");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_l_lt_r);
    tcase_add_test(tc_pos, test_l_gt_r);
    tcase_add_test(tc_pos, test_l_eq_r);
    suite_add_tcase(s, tc_pos);

    return s;
}

