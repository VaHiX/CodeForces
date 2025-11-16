# Problem: CF 1838 E - Count Supersequences
# https://codeforces.com/contest/1838/problem/E

"""
Algorithm: Count Supersequences
Techniques: Modular Arithmetic, Combinatorics, Inclusion-Exclusion Principle

Time Complexity: O(n * log(mod)) per test case due to modular exponentiation
Space Complexity: O(1) additional space (excluding input storage)

This solution uses the inclusion-exclusion principle to count the number of arrays b of size m 
with elements in [1,k] that contain array a as a subsequence.

The approach:
1. Calculate total number of possible arrays of size m with elements in [1,k]: k^m
2. Subtract the count of arrays that do NOT contain a as a subsequence
3. For each position in a, we consider how many ways we can place elements such that 
   a is not a subsequence, using inclusion-exclusion
4. Use modular arithmetic for all calculations to avoid overflow
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def pow(x, y, mod):
    # Fast modular exponentiation
    if x == -1:
        return 1 - y % 2 * 2
    ans, u = 1, x
    while y:
        if y & 1:
            ans = ans * u % mod
        y >>= 1
        u = u * u % mod
    return ans


t = int(input())
mod = 10**9 + 7
ans = []
for _ in range(t):
    n, m, k = map(int, input().split())
    a = list(map(int, input().split()))
    u, v, w = 1, 1, pow(k - 1, m, mod)  # u, v are for combinatorics, w is for the inverse
    inv = pow(k - 1, mod - 2, mod)  # Modular inverse of (k-1)
    ng = 0  # count of invalid sequences
    for i in range(n):
        # Add contribution of current element to invalid count using inclusion-exclusion
        ng += u * pow(v, mod - 2, mod) % mod * w % mod
        u, v, w = u * (m - i) % mod, v * (i + 1) % mod, w * inv % mod
    ans0 = (pow(k, m, mod) - ng) % mod  # Total - Invalid = Valid
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/