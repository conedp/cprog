#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

task="./app.exe"
true_out=$(basename "$2")".temp"
args_name="$1"
expect_out="$2"


if ! [ -f "$args_name" ] || ! [ -f "$expect_out" ] ; then
    echo wrong file/s
    exit 2
fi

if ! [ -f "$task" ] ; then
    echo "app.exe does not exist"
    exit 3
fi

read -r args_array < "$args_name"

eval set -- "$args_array"

"$task" "$@">"$true_out"

if "func_tests/scripts/"comparator.sh "$true_out" "$expect_out" ; then
    exit 0
else
    exit 1
fi
