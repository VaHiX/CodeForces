# Problem: CF 2038 D - Divide OR Conquer
# https://codeforces.com/contest/2038/problem/D

"""
Algorithm: Dynamic Programming with Segment Tree for Range OR Queries
Time Complexity: O(n * log(n) * log(n)) 
Space Complexity: O(n * log(n))

This solution uses dynamic programming with a sparse table for efficient range OR queries.
The idea is to build a DP table where dp[i][x] represents the number of ways to split
the array up to index i such that the last segment has OR value x.

We maintain a segment tree (sparse table) to quickly compute the OR of any subarray.
For each position i, we update the dp table based on previous states and also perform
binary search to find valid extensions of segments that maintain non-decreasing OR values.
"""

import sys

mod = 998244353
n, *rest = map(int, sys.stdin.read().split())
a = [0] + rest[:n]
k = n.bit_length()
st = [[0] * (n + 2) for _ in range(k + 1)]
for i in range(1, n + 1):
    st[0][i] = a[i]
for j in range(1, k + 1):
    for i in range(1, n + 1 - (1 << j) + 1):
        st[j][i] = st[j - 1][i] | st[j - 1][i + (1 << (j - 1))]


def query_or(l, r):
    # Helper function to compute OR of elements from index l to r using sparse table
    length = r - l + 1
    j = length.bit_length() - 1
    return st[j][l] | st[j][r - (1 << j) + 1]


vals = [{} for _ in range(n + 2)]
vals[1][a[1]] = 0
for i in range(2, n + 1):
    vals[i][a[i]] = 0
    for x in vals[i - 1]:
        new_x = x | a[i]
        vals[i][new_x] = vals[i].get(new_x, 0) + vals[i - 1][x]
dp = [{} for _ in range(n + 2)]
dp[1][a[1]] = 1
for i in range(1, n):
    for x in dp[i]:
        cnt = dp[i][x]
        new_x = x | a[i + 1]
        dp[i + 1][new_x] = (dp[i + 1].get(new_x, 0) + cnt) % mod
        l, r = i + 1, n
        res = n + 1
        while l <= r:
            mid = (l + r) // 2
            if query_or(i + 1, mid) >= x:
                res = mid
                r = mid - 1
            else:
                l = mid + 1
        if res <= n:
            seg_x = query_or(i + 1, res)
            dp[res][seg_x] = (dp[res].get(seg_x, 0) + cnt) % mod
ans = sum(dp[n].values()) % mod
print(ans)


# https://github.com/VaHiX/CodeForces/