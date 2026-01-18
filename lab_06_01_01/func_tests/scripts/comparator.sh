#!/bin/bash

if ! [ -f "$1" ] || ! [ -f "$2" ] ; then
    echo wrong arguments
fi

FILE1=$(mktemp)
FILE2=$(mktemp)

t=$(tr -s '\r\n' ' ' < "$1")
echo "${t#*Result: }" > "$FILE1"

t=$(tr -s '\r\n' ' ' < "$2")
echo "${t#*Result: }" > "$FILE2"

if cmp -s "$FILE1" "$FILE2" ; then
    exit 0
else
    exit 1
fi

rm "$FILE1"
rm "$FILE2"
