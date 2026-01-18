#!/bin/bash

verbose_flag=0
valgr_flag=0
if [[ $1 == "-v" ]] || [[ $1 == "--verbose" ]]; then
    verbose_flag=1
elif [[ $1 == "-mem" ]] || [[ $1 == "--memory" ]]; then
    valgr_flag=1
fi
shift
if [[ $1 == "-v" ]] || [[ $1 == "--verbose" ]]; then
    verbose_flag=1
elif [[ $1 == "-mem" ]] || [[ $1 == "--memory" ]]; then
    valgr_flag=1
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
for args_name in "func_tests/data/"pos*args.txt ; do
    args_name_base=$(basename "$args_name")
    outname="${args_name//args/out}"
    if [[ $valgr_flag == "1" ]] ; then
        echo "${args_name_base//_args.txt/}"
        if ! "func_tests/scripts/pos_case.sh" "$args_name" "$outname" -mem ; then
            counter_pos_fail=$((counter_pos_fail + 1))
            if [[ $verbose_flag == "1" ]] ; then
                echo "${args_name_base//_args.txt/}" failed
            fi
        fi
    else
        if ! "func_tests/scripts/pos_case.sh" "$args_name" "$outname" ; then
            counter_pos_fail=$((counter_pos_fail + 1))
            if [[ $verbose_flag == "1" ]] ; then
                echo "${args_name_base//_args.txt/}" failed
            fi
        fi
    fi
    counter_pos=$((counter_pos + 1))
done

# negative cases
for args_name in "func_tests/data/"neg*args.txt ; do
    args_name_base=$(basename "$args_name")
    if [[ $valgr_flag == "1" ]] ; then
        echo "${args_name_base//_args.txt/}"
        if ! "func_tests/scripts/neg_case.sh" "$args_name" -mem ; then
            counter_neg_fail=$((counter_neg_fail + 1))
            if [[ $verbose_flag == "1" ]] ; then
                echo "${args_name_base//_args.txt/}" failed
            fi
        fi
    else
        if ! "func_tests/scripts/neg_case.sh" "$args_name" ; then
            counter_neg_fail=$((counter_neg_fail + 1))
            if [[ $verbose_flag == "1" ]] ; then
                echo "${args_name_base//_args.txt/}" failed
            fi
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
s
