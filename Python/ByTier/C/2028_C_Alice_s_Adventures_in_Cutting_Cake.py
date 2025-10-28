# Problem: CF 2028 C - Alice's Adventures in Cutting Cake
# https://codeforces.com/contest/2028/problem/C

"""
Algorithm: Binary Search + Prefix Sum + Greedy
Time Complexity: O(n log(sum of elements))
Space Complexity: O(n)

This problem involves partitioning a cake into m+1 pieces such that each of the m creatures gets a piece with tastiness >= v,
and Alice wants to maximize her own piece's tastiness.

The approach:
1. First, we greedily find left partition points so that each piece has tastiness >= v.
2. Then, we greedily find right partition points so that each piece has tastiness >= v.
3. Using prefix sums, we check all valid combinations of left and right partitions to find maximum tastiness Alice can get.
4. We use binary search over the possible answer to find the maximum.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
t = int(input())
ans = []
for _ in range(t):
    n, m, v = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array for easier processing
    l, r = [-1] * (m + 1), [-1] * (m + 1)  # l[i]: leftmost index of i-th piece, r[i]: rightmost index of i-th piece
    l[0], r[0] = 0, n
    u, j = 0, 1
    for i in range(1, n + 1):
        u += a[i]
        if u >= v:
            l[j], u, j = i, 0, j + 1  # Found boundary of piece j
        if j > m:
            break
    u, j = 0, 1
    for i in range(n, 0, -1):
        u += a[i]
        if u >= v:
            r[j], u, j = i - 1, 0, j + 1  # Found boundary of piece j from the end
        if j > m:
            break
    # Compute prefix sum
    for i in range(1, n + 1):
        a[i] += a[i - 1]
    ans0 = -1
    # Try all valid splits to maximize Alice's piece
    for i in range(m + 1):
        if r[i] != -1 and l[m - i] != -1:
            ans0 = max(ans0, a[r[i]] - a[l[m - i]])
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/