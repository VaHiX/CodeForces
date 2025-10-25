# Problem: CF 2008 C - Longest Good Array
# https://codeforces.com/contest/2008/problem/C

"""
C. Longest Good Array

Purpose:
This code finds the maximum length of a "good" array that can be constructed 
with elements constrained between l and r. A good array satisfies:
1. It is strictly increasing.
2. The differences between adjacent elements are also strictly increasing.

Algorithm:
The approach uses mathematical derivation to find the maximum possible length
by modeling the problem as finding the largest n such that the sum of first 
(n-1) natural numbers (1 + 2 + ... + (n-1)) does not exceed (r - l).

Time Complexity: O(1)
Space Complexity: O(1)

The formula used:
For a good array of length n, minimal required range is:
1 + 2 + ... + (n-1) = (n-1)*n/2
So we solve for the largest n such that (n-1)*n/2 <= r - l.
This leads to quadratic equation: n^2 - n - 2*(r-l) <= 0
Using quadratic formula: n = (1 + sqrt(1 + 8*(r-l))) / 2
"""

for _ in range(int(input())):
    l, r = map(int, input().split())
    # Formula to compute the maximum length of a good array
    print(int(((1 + 8 * (r - l)) ** 0.5 - 1) // 2 + 1))


# https://github.com/VaHiX/codeForces/