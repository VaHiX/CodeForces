# Problem: CF 1999 A - A+B Again?
# https://codeforces.com/contest/1999/problem/A

"""
Algorithm: Digit Sum Calculation
Techniques: String manipulation, basic arithmetic operations

Time Complexity: O(t) where t is the number of test cases, as we process each test case in constant time O(1)
Space Complexity: O(1) as we only use a constant amount of extra space

This solution takes each two-digit number as a string, extracts the first and second digits,
converts them back to integers, and sums them up.
"""

for ti in range(int(input())):  # Read number of test cases and iterate through each
    n = input()  # Read the two-digit number as a string
    print(int(n[0]) + int(n[1]))  # Extract first and second digit, convert to int and sum them


# https://github.com/VaHiX/CodeForces/