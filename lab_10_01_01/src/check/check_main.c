#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include "check_helpers.h"
#include "check_find.h"
#include "check_insert.h"
#include "check_remove_duplicates.h"
#include "check_sorted_insert.h"
#include "check_sort.h"


int main(void)
{
    SRunner *sr;
    int number_failed = 0;

    sr = srunner_create(find_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(insert_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(remove_duplicates_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(sorted_insert_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(sort_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
