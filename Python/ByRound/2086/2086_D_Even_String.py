# Problem: CF 2086 D - Even String
# https://codeforces.com/contest/2086/problem/D

"""
D. Even String
Task: Count the number of distinct strings where for every pair of indices i and j such that s[i] = s[j], 
the difference |i - j| is even. This implies that all occurrences of a character must be at even or odd positions.

Approach:
- The condition implies that characters appearing in the string must occupy either all even-indexed positions or all odd-indexed positions.
- So we can split the problem into two cases: placing characters at even indices and odd indices.
- This is a combinatorial problem involving partitions of letters into two groups (even/odd positions), followed by arranging those letters.

Complexity:
Time: O(sum(c) * sum(c) / 2) per test case due to dynamic programming on subset sums
Space: O(sum(c)) for storing factorials and DP array

Algorithms/Techniques:
- Dynamic Programming for subset sum counting
- Modular arithmetic and precomputed factorials
- Inclusion-exclusion or combinatorial distribution logic
"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
mod = 998244353
nm = 10**6
fact = [1] * (nm + 1)
for i in range(2, nm + 1):
    fact[i] = fact[i - 1] * i % mod
T = sint()
for _ in range(T):
    a = aint()
    tot = sum(a)  # Total number of letters
    even = tot // 2  # Half of total (number of even positions if string length is even)
    dp = [1] + [0] * even  # DP array for subset sums
    tmp = 1  # Temporary variable to store product of factorials
    for i in a:
        if i == 0:
            continue  # Skip zero counts
        # Iterate backwards to avoid using updated values in same iteration
        for j in range(even, i - 1, -1):
            dp[j] = (dp[j] + dp[j - i]) % mod
        tmp = (tmp * fact[i]) % mod  # Accumulate factorial product of counts
    ans = fact[tot - even] * fact[even] * pow(tmp, -1, mod) * dp[-1]
    ans %= mod
    print(ans)


# https://github.com/VaHiX/codeForces/