# Problem: CF 2039 C2 - Shohag Loves XOR (Hard Version)
# https://codeforces.com/contest/2039/problem/C2

"""
C2. Shohag Loves XOR (Hard Version)

Problem Description:
Given two integers x and m, count the number of integers y such that 1 <= y <= m and (x ^ y) is divisible by either x, y, or both.

Algorithm:
This solution uses mathematical analysis combined with direct brute-force for small values of y up to min(x, y), then handles the rest using modular arithmetic optimizations.

Time Complexity: O(min(x, y) + log(m)) per test case
Space Complexity: O(1)

Techniques Used:
- Bitwise XOR operations
- Modular arithmetic
- Mathematical optimization for large ranges
"""

import sys

input = sys.stdin.readline


def li():
    return [int(i) for i in input().split()]


for w in range(int(input())):
    x, y = li()
    ans = 0
    # Check all y from 1 to min(x, y)
    for i in range(1, min(x, y) + 1):
        if (x ^ i) % i == 0:
            ans += 1
    # Handle cases where y > x
    if y > x:
        # Add count of valid y values in the range [x+1, y] that satisfy condition
        # These are multiples of x shifted appropriately
        ans += (y - x) // x
        # Compute a special value e for edge case testing
        e = y - y % x + x
        if x < e ^ x <= y:
            ans += 1
        # Another adjustment based on XOR and boundary checks
        e = y - y % x
        e = e ^ x
        if y >= 2 * x and (e <= x or e > y):
            ans -= 1
    print(ans)


# https://github.com/VaHiX/codeForces/