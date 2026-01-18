#!/bin/bash

if ! [ -f "$1" ] || ! [ -f "$2" ] ; then
    echo wrong arguments
fi

if cmp -s "$1" "$2" ; then
    exit 0
else
    exit 1
fi

