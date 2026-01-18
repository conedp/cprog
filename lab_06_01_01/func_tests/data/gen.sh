#!/bin/bash

i=10
while [ $i -le 35 ] ; do
    echo "func_tests/data/pos_${i}_in.txt" > "./pos_${i}_args.txt"
    i=$((i + 1))
done
