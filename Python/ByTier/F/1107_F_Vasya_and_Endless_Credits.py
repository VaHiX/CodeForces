# Problem: CF 1107 F - Vasya and Endless Credits
# https://codeforces.com/contest/1107/problem/F

"""
F. Vasya and Endless Credits

Algorithm: Dynamic Programming with State Compression
Time Complexity: O(n^2)
Space Complexity: O(n)

The problem involves selecting credit offers optimally to maximize the amount of money 
available at some point in the future. Each offer gives an initial amount (a_i) and 
requires monthly payments (b_i) for k_i months.

Approach:
- Use dynamic programming where dp[j] represents the maximum money achievable 
  with exactly j active credits.
- For each offer, calculate its "priority" based on b_i * (i << 10) to prioritize offers.
- Sort by priority in descending order to process better offers first.
- Update DP state considering both taking and not taking each credit offer.

The value f(u, v) = u << 10 ^ v is used as a hash-like measure for sorting purposes,
where the lower bits represent the index to keep track during sorting.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 10 ^ v


n = int(input())
a0, b0, k0 = [0] * n, [0] * n, [0] * n
for i in range(n):
    a, b, k = map(int, input().split())
    a0[i], b0[i], k0[i] = a, b, k
u = [f(b0[i], i) for i in range(n)]  # Priority calculation using bit manipulation and index
u = [i & 0x3FF for i in sorted(u, reverse=True)]  # Sort by priority and mask to get indices
dp = [0] * (n + 1)
for i in range(1, n + 1):
    j = u[i - 1]
    a, b, k = a0[j], b0[j], k0[j]
    dp0 = [0] * (n + 1)
    x = max(a - b * k, 0)  # Calculate gain from taking current offer
    for j in range(i, -1, -1):  # Iterate backwards through possible numbers of active credits
        dp0[j] = max(dp[j] + x, dp[j - 1] + a - b * (j - 1)) if j else dp[j] + x  # Update DP
    dp = dp0
ans = max(dp)
print(ans)


# https://github.com/VaHiX/codeForces/