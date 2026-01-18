#!/bin/bash

verbose_flag=0
if [[ $1 == "-v" ]] || [[ $1 == "--verbose" ]]; then
    verbose_flag=1
fi
dir=$(pwd | sed 's!.*/!!g')

if [ "$dir" == "scripts" ] || [ "$dir" == "data"  ] ; then
    cd ../../
fi

if [ "$dir" == "func_tests" ] ; then
    cd ../
fi

if ! [ -e "./app.exe" ] ; then
    echo "./app.exe" doesn\'t exist
    exit 2
fi

counter_pos_fail=0
counter_neg_fail=0
counter_pos=0
counter_neg=0
# positive cases
for inname in "func_tests/data/"pos*in.txt ; do
    inname=$(basename "$inname")
    outname="${inname//in/out}"
    if ! "func_tests/scripts/pos_case.sh" "$inname" "$outname" ; then
        counter_pos_fail=$((counter_pos_fail + 1))
        if [[ $verbose_flag == "1" ]] ; then
            echo "${inname//_in.txt/}" failed
        fi
    fi
    counter_pos=$((counter_pos + 1))
done

# negative cases
for inname in "func_tests/data/"neg*in.txt ; do
    inname=$(basename "$inname")
    if ! "func_tests/scripts/neg_case.sh" "$inname" ; then
        counter_neg_fail=$((counter_neg_fail + 1))
        if [[ $verbose_flag == "1" ]] ; then
            echo "${inname//_in.txt/}" failed
        fi
    fi
    counter_neg=$((counter_neg + 1))
done

echo failed "$counter_pos_fail" out of "$counter_pos" positive
echo failed "$counter_neg_fail" out of "$counter_neg" negative

if [ $((counter_pos_fail + counter_neg_fail)) -ne 0 ] ; then
    exit $((counter_pos_fail + counter_neg_fail))
else
    echo all correct
    exit 0
fi
