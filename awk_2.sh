#!/bin/bash

for arg in $@
do
    awk 'BEGIN{c=0; v=0}
    {
     	v+=gsub(/[aeiouAEIOU]/,"")
        c+=gsub(/[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]/,"")
    }
    END {print FILENAME " " v " " c}' $arg
done;

