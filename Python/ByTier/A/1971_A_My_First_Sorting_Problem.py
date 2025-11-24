# Problem: CF 1971 A - My First Sorting Problem
# https://codeforces.com/contest/1971/problem/A

"""
Problem: A. My First Sorting Problem
Algorithm: Simple comparison and sorting of two integers
Time Complexity: O(1) - constant time operations (min, max, split, etc.)
Space Complexity: O(1) - constant space usage (only storing two integers)

This problem requires finding the minimum and maximum of two given integers
and outputting them in the order: minimum first, then maximum.
The solution uses built-in min() and max() functions which operate in constant time.
"""

for _ in range(int(input())):  # Read number of test cases and loop through them
    x, y = map(int, input().split())  # Parse the two integers from input line
    print(min(x, y), max(x, y))  # Output minimum and maximum of the two numbers


# https://github.com/VaHiX/CodeForces/