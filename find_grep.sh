#!/bin/bash

find ./$1 -type f -name "*.c" |
while read f;
do
	val=$(grep -c "^#include <*.*>$" "$f")
	if [ $val -ge 3 ]
	then
		echo "$(basename "$f")"
	fi;
done;

