#!/bin/bash

prefix="./"
dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

task=$prefix"app.exe"
inname=$prefix"func_tests/data/"$1

if ! [ -f "$inname" ] ; then
    echo wrong file/s
    exit 2
fi

if $task<"$inname">/dev/null ; then
    exit 1
else
    exit 0
fi
