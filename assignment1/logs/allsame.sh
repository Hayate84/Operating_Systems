#!/usr/bin/bash

test_file=Thread_main

for file in `ls`; do
    diff $test_file $file
done
