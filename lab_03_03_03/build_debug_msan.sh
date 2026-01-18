#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi


clang -std=c99 -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -g -fsanitize=leak -fno-omit-frame-pointer -fPIE ./*.c

clang -o "app.exe" ./*.o -lm -fsanitize=leak -pie -fno-omit-frame-pointer
