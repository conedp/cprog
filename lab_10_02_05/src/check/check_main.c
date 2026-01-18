#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include "check_helpers.h"
#include "check_concatenate.h"
#include "check_delete_excess_spaces.h"
#include "check_find_substring.h"


int main(void)
{
    SRunner *sr;
    int number_failed = 0;

    sr = srunner_create(concatenate_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(delete_excess_spaces_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    sr = srunner_create(find_substring_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
