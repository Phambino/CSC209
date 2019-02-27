#!/bin/bash

declare -i at=0
declare -i amax=0
declare -i labt=0
declare -i labmax=0

for d in a1 a2 a3 a4; do

if [ -d "../$d" ]; then
	if [ -f "../$d/feedback.txt" ]; then
		grade=`tail -n1  "../$d/feedback.txt" | tr -d [:blank:]`
		IFS='/' read -ra grArray <<< "$grade"
		score=${grArray[0]}
		max=${grArray[1]}
		at=$at+$score
		amax=$amax+$max
		echo "$d: $score/$max"
	else
	echo "$d: -/-"
	fi 
else
echo "$d: -/-"
fi
done

echo

for d in w1 w2 w3 w4 w5 w6 w7 w8 w9 w10 w11; do

if [ -d "../$d" ]; then
        if [ -f "../$d/feedback.txt" ]; then
                grade=`tail -n1  "../$d/feedback.txt" | tr -d [:blank:]`
                IFS='/' read -ra grArray <<< "$grade"
                score=${grArray[0]}
                max=${grArray[1]}
                labt=$labt+$score
                labmax=$labmax+$max
                echo "$d: $score/$max"
        else
        echo "$d: -/-"
        fi
else
echo "$d: -/-"
fi
done

echo
if [ $amax == 0 ]; then
	echo "Assignment Total: - / -"
else
	echo "Assignment Total: $at / $amax"
fi

if [ $labmax == 0 ]; then
	echo "Lab Total: - / -"
else
	echo "Lab Total: $labt / $labmax"
fi

