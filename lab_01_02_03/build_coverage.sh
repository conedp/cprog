#!/bin/bash

prefix="./"
dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

gcc -std=c99 -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -O0 -g3 --coverage -o $prefix"main.o" $prefix"main.c"

gcc -o $prefix"app.exe" $prefix"main.o" -lm --coverage
