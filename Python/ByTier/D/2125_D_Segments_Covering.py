# Problem: CF 2125 D - Segments Covering
# https://codeforces.com/contest/2125/problem/D

"""
D. Segments Covering

Purpose:
This code calculates the probability that each cell in a linear strip of m cells is covered by exactly one segment,
given n segments with associated probabilities. It uses dynamic programming and probability calculations.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Modular Exponentiation
- Prefix Sum / Range Update Technique

Time Complexity: O(n log mod + m)
Space Complexity: O(n + m)

The problem is solved using a backward DP approach where for each segment, we compute the probability it contributes
to a cell being covered. The final result is scaled by the global probability of all segments being valid.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
n, m = map(int, input().split())
mod = 998244353
nxt = [[] for i in range(m)]  # nxt[i] stores (end, probability) pairs that cover position i
az = 1  # Global probability of all segments being valid


def pw(a, b):
    """Modular exponentiation: computes a^b mod mod efficiently."""
    ret = 1
    while b:
        if b & 1:
            ret = ret * a % mod
        a = a * a % mod
        b >>= 1
    return ret


for i in range(n):
    l, r, p, q = map(int, input().split())
    l -= 1  # Convert to 0-based indexing
    # Multiply global probability by the inverse of total segment probability
    az *= (q - p) * pw(q, mod - 2) % mod
    az %= mod
    # Add this segment's contribution to the graph for positions from l to r-1
    nxt[l].append((r, p * pw(q - p, mod - 2) % mod))

dp = [0] * (m + 1)
dp[m] = 1  # Base case: probability of covering from m onwards is 1

# Backward DP to calculate probability of reaching each position
for i in range(m - 1, -1, -1):
    for nx, pr in nxt[i]:  # For all segments that extend from position i
        dp[i] += pr * dp[nx] % mod  # Accumulate probability

# Final result: multiply the DP result with global probability
print(dp[0] * az % mod)


# https://github.com/VaHiX/codeForces/