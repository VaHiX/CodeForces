# Problem: CF 1950 D - Product of Binary Decimals
# https://codeforces.com/contest/1950/problem/D

"""
Algorithm: Dynamic Programming with Precomputed Binary Decimals
Approach:
- Precompute all binary decimals up to the maximum input number M.
- Use dynamic programming to determine if a number can be represented as a product of these binary decimals.
- A binary decimal is a number whose digits are only 0 or 1, and it must start with 1.
- For each number from 1 to M, if it's reachable (dp[i] = True), we try multiplying it with all binary decimals <= M.

Time Complexity: O(M * log(M)) where M is the maximum value in inputs.
Space Complexity: O(M + 2^(log(M))) for dp array and binary decimals list.

Techniques:
- Precomputation of binary decimals
- Dynamic Programming
- itertools.product for generating combinations
"""

import itertools
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
t, *vals = data
M = max(vals)
B = []
for L in range(1, len(str(M)) + 1):
    for bits in itertools.product("01", repeat=L - 1):
        x = int("1" + "".join(bits))
        if x <= M:
            B.append(x)
dp = [False] * (M + 1)
dp[1] = True
for i in range(1, M + 1):
    if dp[i]:
        for b in B:
            v = i * b
            if v > M:
                break
            dp[v] = True
out = []
for n in vals:
    out.append("YES" if dp[n] else "NO")
sys.stdout.write("\n".join(out))


# https://github.com/VaHiX/CodeForces/