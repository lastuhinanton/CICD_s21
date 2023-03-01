#!/bin/bash

clang-format -style=google -n *.c 2> test.tmp

count=$(cat test.tmp | wc -l)
if [[ $count != 0 ]]; then
    exit 1
else
    exit 0
fi
