#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

rm -f app.exe
rm -f main.o
rm -f ./*.temp
rm -f ./*.gcda
rm -f ./*.gcno
rm -f ./*.gcov
