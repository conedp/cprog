#include <check.h>
#include <stdlib.h>

#include "check_assoc_array_insert.h"
#include "check_assoc_array_find.h"
#include "check_assoc_array_remove.h"
#include "check_assoc_array_clear.h"
#include "check_assoc_array_each.h"
#include "check_assoc_array_min.h"
#include "check_assoc_array_max.h"


int main(void)
{
    SRunner *sr;
    int number_failed = 0;

    sr = srunner_create(assoc_array_insert_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_find_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_remove_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_clear_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_each_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_min_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(assoc_array_max_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
