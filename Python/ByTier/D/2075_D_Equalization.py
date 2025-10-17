# Problem: CF 2075 D - Equalization
# https://codeforces.com/contest/2075/problem/D

"""
D. Equalization

Problem Description:
Given two non-negative integers x and y, we can perform operations to make them equal.
Each operation allows choosing a positive integer k and dividing either x or y by 2^k (rounded down),
with the cost of 2^k. Each value of k may be used at most once.

Algorithm:
- Uses dynamic programming with bit manipulation.
- Precomputes minimum cost states using a function f(u,v) = u << 7 ^ v to map 2D to 1D.
- The DP tracks minimal cost for reducing x and y down to various bit lengths.
- Optimizes by considering only bits that differ between x and y.

Time Complexity: O(30^2 * 2^14) ~ O(10^5)
Space Complexity: O(2^14) ~ O(16384)

"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 7 ^ v  # Bit manipulation to compress (u,v) into a single index


t = int(input())
ans = []
inf = 1 << 62
l = 30
dp = [inf] * (1 << 14)
dp[0] = 0  # Base case: no operations needed when both x and y are 0
for i in range(1, l):  # For each bit position k from 1 to 29
    p = 1 << i  # Cost of operation using bit k (2^k)
    for j in range(3 * l, -1, -1):  # Traverse all valid combinations of (j,k) in reverse order
        for k in range(3 * l, -1, -1):
            mi = inf
            if i <= j:  # Check if we can use this bit on x side
                mi = min(mi, dp[f(j - i, k)] ^ p)  # Use operation on x
            if i <= k:  # Check if we can use this bit on y side
                mi = min(mi, dp[f(j, k - i)] ^ p)  # Use operation on y
            dp[f(j, k)] = min(mi, dp[f(j, k)])  # Update DP state

mi = list(dp)  # Copy DP values to use later for final lookup
for i in range(3 * l, -1, -1):  # Propagate minimal costs forward to avoid overcounting
    for j in range(3 * l, -1, -1):
        mi[f(i, j)] = min(mi[f(i, j)], mi[f(i + 1, j)], mi[f(i, j + 1)])

for _ in range(t):
    x, y = map(int, input().split())
    n, m = x.bit_length(), y.bit_length()  # Get number of bits needed to represent x and y
    ans0 = mi[f(n, m)]  # Minimum cost to reduce both to same bit lengths
    
    # While leading bits match, continue reducing until they differ
    while min(n, m) and x >> (n - 1) == y >> (m - 1):
        n, m = n - 1, m - 1  # Reduce bit-lengths
        ans0 = min(ans0, dp[f(n, m)])  # Update with new minimal cost
    
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/