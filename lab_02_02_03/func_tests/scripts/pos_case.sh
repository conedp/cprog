#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

task="./app.exe"
true_out="./${2}.temp"
inname="./func_tests/data/"$1

$task<"$inname">"$true_out"

expect_out="./func_tests/data/"$2

if ! [ -f "$inname" ] || ! [ -f "$expect_out" ] ; then
    echo wrong file/s
    exit 2
fi

if "func_tests/scripts/"comparator.sh "$true_out" "$expect_out" ; then
    exit 0
else
    exit 1
fi
