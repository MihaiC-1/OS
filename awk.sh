#!/bin/bash

if [ "$#" -lt 1 ]
then
	echo 'Trebuie dat macar un fisier de transport!'
	exit 1
fi

for i in $@
do
	tip=`grep -c "IN" ./$i`
	if [ $tip -eq 1 ]
	then
		awk -F, '{if (NF > 1) sum[$1]+=$2 } 
		END { for (name in sum) print name","sum[name] }' ./depozit.csv ./$i > IN.csv
		grep "" IN.csv > depozit.csv
		rm IN.csv
	else
		awk -F, '{if (NF > 1 && dif[$1] > 0) dif[$1]-=$2;else if (NF > 1) dif[$1]+=$2; }
		END { for (name in dif) print name","dif[name] }' ./depozit.csv ./$i > OUT.csv
		grep "" OUT.csv > depozit.csv
		rm OUT.csv
	fi
done
