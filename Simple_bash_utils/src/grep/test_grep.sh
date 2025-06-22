#!/bin/bash

if [ ! -f "./s21_grep" ]; then
    echo "Error: s21_grep executable not found!"
    make s21_grep
fi

function run_test() {
    local test_description="$1"
    local s21_command="$2"
    local grep_command="$3"

    echo "=== TEST START ==="
    echo "Description: $test_description"
    echo "Command being executed: $s21_command"

    echo "Running s21_grep..."
    bash -c "$s21_command" > s21_grep.txt 2>/dev/null

    echo "Running standard grep..."
    bash -c "$grep_command" > grep.txt 2>/dev/null

    export LC_ALL=C
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"

    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]; then
        echo "✅ TEST SUCCESSFUL"
        ((successful_tests++))
    else
        echo "❌ TEST FAILED"
        echo "$test_description: $s21_command" >> log.txt
        ((failed_tests++))
    fi

    rm -f s21_grep.txt grep.txt
    echo "=== TEST END ==="
    echo
}

successful_tests=0
failed_tests=0
echo "" > log.txt

echo -e "This is pattern1.\nThis is pattern2.\nNothing here." > file1.txt
echo -e "Pattern1 is here.\nAnother pattern2.\nNo match." > file2.txt
echo -e "Pattern1 found here.\nNo match." > file3.txt
echo -e "pattern1\npattern2" > patterns.txt

TEST_FILES=(
    "file1.txt"
    "file2.txt"
    "file3.txt"
)

TEST_PATTERNS=(
    "-e pattern1"
    "-e pattern2"
    "-f patterns.txt"
    "Nothing"
    "-e '\\..*'" 
)

TEST_FLAGS=(
    "-i"    
    "-v"    
    "-c"    
    "-l"    
    "-n"    
    "-h"    
    "-o"    
)

for pattern in "${TEST_PATTERNS[@]}"; do
    for test_file in "${TEST_FILES[@]}"; do
        for flag1 in "${TEST_FLAGS[@]}"; do
            for flag2 in "${TEST_FLAGS[@]}"; do
                if [ "$flag1" != "$flag2" ]; then
                    test_name="Test: $flag1 $flag2 with pattern $pattern"
                    s21_command="./s21_grep $flag1 $flag2 $pattern $test_file"
                    grep_command="grep $flag1 $flag2 $pattern $test_file"
                    run_test "$test_name" "$s21_command" "$grep_command"
                fi
            done
        done
    done
done

test_name="Test with multiple files"
s21_command="./s21_grep -e pattern1 file1.txt file2.txt file3.txt"
grep_command="grep -e pattern1 file1.txt file2.txt file3.txt"
run_test "$test_name" "$s21_command" "$grep_command"

test_name="Test with nonexistent file"
s21_command="./s21_grep -s pattern1 nonexistent.txt file1.txt"
grep_command="grep -s pattern1 nonexistent.txt file1.txt"
run_test "$test_name" "$s21_command" "$grep_command"

rm -f file1.txt file2.txt file3.txt patterns.txt

echo "📊 TEST RESULTS:"
echo "✅ Successful tests: $successful_tests"
echo "❌ Failed tests: $failed_tests"
echo "📝 Details of failed tests are in log.txt"
