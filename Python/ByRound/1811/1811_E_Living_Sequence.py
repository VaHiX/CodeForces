# Problem: CF 1811 E - Living Sequence
# https://codeforces.com/contest/1811/problem/E

"""
Code Purpose:
This code computes the k-th element of a "living sequence" which excludes all numbers containing the digit '4'.
The approach treats the problem as a base-9 conversion, where each digit is adjusted to skip 4.
The mapping is such that digits 0-8 in base-9 correspond to 1-9 in the living sequence (with 4 removed).
This is efficient for large values of k up to 10^12.

Algorithms/Techniques:
- Base-9 conversion with digit mapping
- String manipulation for digit replacement
- Efficient handling of large integers

Time Complexity:
O(log_9(k)) where k <= 10^12, which is effectively O(40) due to the logarithmic nature.

Space Complexity:
O(log_9(k)) for storing the string representation of the base-9 number and intermediate results.
"""

import sys

input = lambda: sys.stdin.readline().strip()

for test in range(int(input())):
    n = int(input())
    s = ""
    while n:
        s += str(n % 9)  # Convert to base-9 digits
        n //= 9
    s = s[::-1]  # Reverse to get correct order
    for i in "87654":  # Adjust digits to skip 4
        s = s.replace(i, str(int(i) + 1))
    print(s)


# https://github.com/VaHiX/CodeForces/