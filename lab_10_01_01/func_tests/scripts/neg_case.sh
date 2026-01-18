#!/bin/bash

dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

task="./app.exe"
args_name="$1"

valgr_flag=0
if [[ $2 == "-mem" ]] ; then
    valgr_flag=1
fi

if ! [ -f "$args_name" ] ; then
    echo wrong file/s
    exit 2
fi

read -r args_array < "$args_name"

eval set -- "$args_array"

if [[ "$valgr_flag" == "1" ]] ; then
    valgrind --leak-check=full --track-origins=yes "$task" "$@"
    if "$task" "$@">/dev/null ; then
        exit 1
    else
        exit 0
    fi
else
    if "$task" "$@">/dev/null ; then
        exit 1
    else
        exit 0
    fi
fi

