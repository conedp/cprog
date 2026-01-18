#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

echo Memory sanitizer
./build_debug_msan.sh
./func_tests/scripts/func_tests.sh -v

echo Address sanitizer
./build_debug_asan.sh
./func_tests/scripts/func_tests.sh -v

echo Undefined behavior sanitizer
./build_debug_ubsan.sh
./func_tests/scripts/func_tests.sh -v
