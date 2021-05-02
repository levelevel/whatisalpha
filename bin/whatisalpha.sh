#!/bin/bash

set -u

TXT=class_ALL.txt

CLASS="alpha alnum upper lower digit xdigit punct blank space cntrl graph print None"

for class in $CLASS
do
    grep "\\b$class" $TXT > class_$class.txt
    echo $class `wc -l < class_$class.txt`
done
