#!/bin/bash

echo "Teeest"

tests=(
"5 -h 0"
"101 -h 0"
"17 -p 0"
"4 -p 0"
"255 -s 0"
"5 -e 0"
"11 -e 1"
"10 -a 0"
"0 -a 1"
"5 -f 0"
"30 -f 1")

for test in "${tests[@]}"; do
    read -r number flag expected <<< "$test"
    ./uwu $number $flag > /dev/null 2>&1
    result=$?
    
    if [ $result -eq $expected ]; then
        echo "0 PASS: $number $flag"
    else
        echo "1 FAIL: $number $flag (ожидание $expected, реальность $result)"
    fi
done

echo "Teeesting completed"