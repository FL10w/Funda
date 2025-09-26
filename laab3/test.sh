#!/bin/bash

PROGRAM="./program"
PASSED=0
FAILED=0

run_test() {
    local command=$1
    local expected_pattern=$2
    local test_name=$3
    
    if eval "$command" 2>/dev/null | grep -q "$expected_pattern"; then
        echo "PASS: $test_name"
        PASSED=$((PASSED + 1))
    else
        echo "FAIL: $test_name"
        FAILED=$((FAILED + 1))
    fi
}

echo "Testing program..."
run_test "$PROGRAM -q 0.000001 1 -3 2" "Два корня" "q: два корня"
run_test "$PROGRAM -m 10 5" "10 кратно 5" "m: кратные числа"
run_test "$PROGRAM -m 10 3" "10 не кратно 3" "m: не кратные числа"
run_test "$PROGRAM -t 0.000001 3 4 5" "прямоугольного треугольника" "t: прямоугольный треугольник"
run_test "$PROGRAM -t 0.000001 3 3 3" "не могут быть сторонами прямоугольного треугольника" "t: не прямоугольный треугольник"
echo
if [ $FAILED -eq 0 ]; then
    echo "All tests passed"
    exit 0
else
    echo "Tests: $((PASSED + FAILED)), Passed: $PASSED, Failed: $FAILED"
    exit 1
fi