# Problem: CF 1906 H - Twin Friends
# https://codeforces.com/contest/1906/problem/H

"""
Code Purpose:
This code solves the problem of counting valid pairs of nicknames (A', B') where:
- A' is a permutation of string A (the elder twin's name)
- B' is obtained by removing exactly (M - N) characters from any permutation of B (the younger twin's name)
- For each position i, B'[i] must be either A'[i] or the next letter in the alphabet after A'[i]

Algorithm:
The solution uses dynamic programming with combinatorics to count valid combinations.
It processes characters in alphabetical order, maintaining DP states for each possible distribution
of characters from A and B that satisfy the constraints.

Time Complexity: O(N * M) where N and M are lengths of the strings
Space Complexity: O(N * M) for the DP table and auxiliary arrays

Techniques:
- Dynamic Programming with combinatorics
- Preprocessing factorials and inverse factorials for combination calculations
- Accumulation of DP states
"""

mod = 998244353
MX = 200001
fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % mod
inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, mod)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % mod


def comb(n: int, k: int) -> int:
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod


from sys import stdin

input = lambda: stdin.readline().rstrip()
from itertools import accumulate


def solve():
    n, m = map(int, input().split())
    c1 = [0] * 27
    c2 = [0] * 27
    for x in input():
        c1[ord(x) - 65] += 1  # Count characters in A
    for x in input():
        c2[ord(x) - 65] += 1  # Count characters in B
    dp = [1]
    tot = 0
    for i in range(26):
        tot += c1[i]
        cnt = comb(tot, c1[i])
        dp = [num * cnt % mod for num in accumulate(dp)]  # Update dp with combinations
        len_dp = min(c1[i], c2[i + 1]) + 1
        ndp = [0] * len_dp
        for j in range(len_dp):
            res = min(c1[i - 1], c2[i] - c1[i] + j)
            if res >= 0:
                ndp[j] = dp[res] * comb(c1[i], j) % mod  # Combine valid states
        dp = ndp
    return sum(dp) % mod


print(solve())


# https://github.com/VaHiX/CodeForces/