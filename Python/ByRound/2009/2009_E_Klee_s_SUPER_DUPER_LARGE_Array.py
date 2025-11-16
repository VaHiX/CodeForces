# Problem: CF 2009 E - Klee's SUPER DUPER LARGE Array!!!
# https://codeforces.com/contest/2009/problem/E

"""
E. Klee's SUPER DUPER LARGE Array!!!
time limit per test2 seconds
memory limit per test256 megabytes

Klee has an array a of length n containing integers [k, k+1, ..., k+n-1] in that order.
Klee wants to choose an index i (1 <= i <= n) such that x = |a1 + a2 + ... + ai - ai+1 - ... - an|
is minimized. Note that for an arbitrary integer z, |z| represents the absolute value of z.

The problem reduces to finding the optimal split point i in the array such that the difference
between the sum of the first i elements and the sum of the remaining (n-i) elements is minimized.

Mathematical derivation shows this can be solved using quadratic formula and binary search techniques
to approximate the integer root, followed by checking two nearest candidates.

Time Complexity: O(1) per test case (constant time arithmetic operations)
Space Complexity: O(1) (only using a constant amount of extra space)

Algorithms/Techniques:
- Mathematical optimization with quadratic equation solving
- Binary search approach using square root approximation
- Integer root finding via floor(sqrt(D)) adjustment

Code Explanation:
- For each test case, define the array as [k, k+1, ..., k+n-1]
- Calculate sum of first i elements: S1 = i*(2*k + i - 1)/2
- Calculate sum of remaining elements: S2 = (n-i)*(2*k + n + i - 2)/2
- Minimize |S1 - S2|
- Derive a quadratic equation in terms of i and solve using sqrt(D) method
"""

import sys

input = sys.stdin.readline
from math import floor, sqrt

f = lambda x: (2 * x * x + x * (4 * k - 2) + (n - n * n - 2 * k * n)) // 2
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    D = 4 * k * k + 4 * k * (n - 1) + (2 * n * n - 2 * n + 1)
    i = (floor(sqrt(D)) - (2 * k - 1)) // 2
    ans = min(abs(f(i)), abs(f(i + 1)))
    print(ans)


# https://github.com/VaHiX/codeForces/