#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

echo build_release
shellcheck ./build_release.sh
echo build_debug
shellcheck ./build_debug.sh
echo build_debug_asan
shellcheck ./build_debug_asan.sh
echo build_debug_msan
shellcheck ./build_debug_msan.sh
echo build_debug_ubsan
shellcheck ./build_debug_ubsan.sh
echo build_coverage
shellcheck ./build_coverage.sh
echo collect_coverage
shellcheck ./collect_coverage.sh
echo clean
shellcheck ./clean.sh
echo sanitizers_testing
shellcheck ./sanitizers_testing.sh
echo func_tests
shellcheck ./func_tests/scripts/func_tests.sh
echo neg_case
shellcheck ./func_tests/scripts/neg_case.sh
echo pos_case
shellcheck ./func_tests/scripts/pos_case.sh
echo comparator
shellcheck ./func_tests/scripts/comparator.sh


