#!/bin/bash

find ./$1 -type f -path "*.txt" | 
while read f;
do
        mv "$f" "${f%.*}.ascii";
done;
