#!/usr/bin/bash

test_file="logs/Thread_main"

for file in `ls logs/`; do
    diff $test_file "logs/"$file
done
