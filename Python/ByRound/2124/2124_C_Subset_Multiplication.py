# Problem: CF 2124 C - Subset Multiplication
# https://codeforces.com/contest/2124/problem/C

"""
C. Subset Multiplication

Given an array b that could be derived from a "beautiful" array a (where each element divides the next),
by multiplying some subset of elements of a by a positive integer x, we need to find any valid value of x.

The algorithm:
- For each adjacent pair in the array, compute lcm(b[i]/gcd(b[i], b[i+1]), b[i+1]/gcd(b[i], b[i+1]))
  This ensures that we are considering the structure where x is part of the pattern.
- The result gives us a candidate value for x.

Time Complexity: O(n * log(max(b))) due to GCD and LCM computation per pair
Space Complexity: O(1) as only scalar variables are used
"""

from math import *

for _ in range(int(input())):
    n = int(input())
    b = list(map(int, input().split()))
    x = 1
    for i in range(n - 1):
        # Compute lcm of (b[i] // gcd(b[i], b[i+1])) and (b[i+1] // gcd(b[i], b[i+1]))
        # This helps determine the multiplier x that would make the pattern consistent.
        x = lcm(x, b[i] // gcd(b[i], b[i + 1]))
    print(x)


# https://github.com/VaHiX/codeForces/