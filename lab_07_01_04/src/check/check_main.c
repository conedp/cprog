#include "check_cmp_uni_int.h"
#include "check_da_alloc.h"
#include "check_key.h"
#include "check_mysort.h"
#include "check_swap_uni.h"
#include <stdlib.h>
#include <check.h>
#include <stdio.h>


int main(void)
{
    int da_alloc_failed, swap_uni_failed, cmp_uni_int_failed, mysort_failed, key_failed;
    Suite *s_da_alloc, *s_swap_uni, *s_cmp_uni_int, *s_mysort, *s_key;
    SRunner *runner_da_alloc, *runner_swap_uni, *runner_cmp_uni_int, *runner_mysort, *runner_key;

    s_da_alloc = da_alloc_suite();
    s_swap_uni = swap_uni_suite();
    s_cmp_uni_int = cmp_uni_int_suite();
    s_mysort = mysort_suite();
    s_key = key_suite();

    runner_da_alloc = srunner_create(s_da_alloc);
    da_alloc_failed = srunner_ntests_failed(runner_da_alloc);
    // Закомментировано чтобы система тестирования на сервере работала корректно
    //printf("da_alloc failed: %d\n", da_alloc_failed);
    srunner_free(runner_da_alloc);

    runner_swap_uni = srunner_create(s_swap_uni);
    swap_uni_failed = srunner_ntests_failed(runner_swap_uni);
    // Закомментировано чтобы система тестирования на сервере работала корректно
    //printf("swap_uni failed: %d\n", swap_uni_failed);
    srunner_free(runner_swap_uni);

    runner_cmp_uni_int = srunner_create(s_cmp_uni_int);
    cmp_uni_int_failed = srunner_ntests_failed(runner_cmp_uni_int);
    // Закомментировано чтобы система тестирования на сервере работала корректно
    //printf("cmp_uni_int failed: %d\n", cmp_uni_int_failed);
    srunner_free(runner_cmp_uni_int);

    runner_mysort = srunner_create(s_mysort);
    mysort_failed = srunner_ntests_failed(runner_mysort);
    // Закомментировано чтобы система тестирования на сервере работала корректно
    //printf("mysort failed: %d\n", mysort_failed);
    srunner_free(runner_mysort);

    runner_key = srunner_create(s_key);
    key_failed = srunner_ntests_failed(runner_key);
    // Закомментировано чтобы система тестирования на сервере работала корректно
    //printf("key failed: %d\n", key_failed);
    srunner_free(runner_key);

    return (da_alloc_failed + swap_uni_failed + cmp_uni_int_failed + mysort_failed + key_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
