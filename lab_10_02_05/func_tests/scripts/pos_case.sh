#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

task="./app.exe"
true_out="./out/${2}.temp"
inname="./func_tests/data/"$1
expect_out="./func_tests/data/"$2

valgr_flag=0
if [[ $3 == "-mem" ]] ; then
    valgr_flag=1
fi


if ! [ -f "$inname" ] || ! [ -f "$expect_out" ] ; then
    echo wrong file/s
    exit 2
fi

if ! [ -f "$task" ] ; then
    echo "app.exe does not exist"
    exit 3
fi

if [[ "$valgr_flag" == "1" ]] ; then
    valgrind --leak-check=full --track-origins=yes $task<"$inname">"$true_out"
else
    $task<"$inname">"$true_out"
fi

if "func_tests/scripts/"comparator.sh "$true_out" "$expect_out" ; then
    exit 0
else
    exit 1
fi
