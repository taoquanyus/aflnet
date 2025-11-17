#!/bin/bash

echo "Testing my_test_case with various inputs..."

echo "Test 1: Empty input"
echo -n "" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 2: VULNTEST pattern"
echo -n "VULNTEST" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 3: Simple VULN pattern"
echo -n "VULN" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 4: Math operation 3+4="
echo -n "3+4=" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 5: Math operation with large result"
echo -n "7+8=" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 6: Palindrome (aba)"
echo -n "aba" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 7: Long palindrome (>10 chars)"
echo -n "abcdefghhgfedcba" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 8: Long input (>50 chars)"
input=$(printf 'a%.0s' {1..60})
echo -n "$input" | ./my_test_case
echo "Exit code: $?"
echo

echo "Test 9: Default case"
echo -n "hello world" | ./my_test_case
echo "Exit code: $?"
echo

echo "All tests completed!"