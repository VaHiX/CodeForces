# Problem: CF 2086 E - Zebra-like Numbers
# https://codeforces.com/contest/2086/problem/E

"""
E. Zebra-like Numbers

Algorithm:
This solution uses dynamic programming with bitmasking to precompute the number of ways to represent numbers as sums of zebra-like numbers.
It then uses a digit DP (Dynamic Programming) approach to count how many valid numbers in range [l, r] have a zebra value of exactly k.

Approach:
1. Precompute zebra-like numbers and transition states using bit operations.
2. Use dynamic programming on masks to compute counts of valid representations.
3. Implement digit DP for efficient counting over large ranges [l, r].

Time Complexity: O(30 * m * 4 + t * log(r)) where m = 120
Space Complexity: O(2^12 + 30 * m) 
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Bitwise operation used for transitioning between states in DP
    return u << 7 ^ v


def g(u, k):
    # Digit DP function that counts valid representations up to number u with exactly k zebra numbers
    if k >= m:
        return 0
    elif u <= 4:
        return 1 if k <= u else 0
    ans = 0
    while u > 4 and k >= 0:
        for i in range(1, 30):
            # Compare with precomputed boundaries x[i]
            if u < x[i]:
                ans += dp[f(i - 1, k)]
                u, k = u - x[i - 1] - 1, k - 1
                break
            elif u == x[i]:
                ans += dp[f(i, k)]
                return ans
    if 0 <= k <= u:
        ans += 1
    return ans


t = int(input())
ans = []
m = 120
x, u = [], 1
for _ in range(30):
    x.append(u << 2)
    u = u << 2 ^ 1  # Left shift by 2 then XOR with 1 to generate powers of 4 alternating pattern

# DP array for memoization. Size is (1<<12) because we use 12 bits for mask
dp = [0] * (1 << 12)
dp[0] = dp[1] = dp[2] = dp[3] = dp[4] = 1  # Base cases

# Fill DP table using transitions based on zebra-like number properties
for i in range(1, 30):
    for j in range(m):
        if not dp[f(i - 1, j)]:
            break
        c = dp[f(i - 1, j)]
        for k in range(4):  # Loop over possible additions (from 0 to 3)
            dp[f(i, j + k)] += c
    dp[f(i, 4)] += 1  # Additional update for state f(i, 4)

# Process each test case
for _ in range(t):
    l, r, k = map(int, input().split())
    ans0 = g(r, k) - g(l - 1, k)
    ans.append(ans0)

sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/