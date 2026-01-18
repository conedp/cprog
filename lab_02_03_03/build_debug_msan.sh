#!/bin/bash

prefix="./"
dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi


clang -std=c99 -c -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -g -fsanitize=leak -fno-omit-frame-pointer -fPIE -o $prefix"main.o" $prefix"main.c"

clang -o $prefix"app.exe" $prefix"main.o" -lm -fsanitize=leak -fPIE -pie -fno-omit-frame-pointer
