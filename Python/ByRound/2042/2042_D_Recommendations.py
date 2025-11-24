# Problem: CF 2042 D - Recommendations
# https://codeforces.com/contest/2042/problem/D

"""
D. Recommendations

Algorithm:
This problem involves finding "strongly recommended" tracks for each user based on their liked segments and predictors.
A predictor for a user is another user whose liked segment fully contains the current user's segment.
Strongly recommended tracks are those liked by all predictors but not by the user themselves.

Approach:
1. For each user, we find all predictors: users whose segment completely covers the current user's segment.
2. The strongly recommended tracks for a user are the tracks that are in ALL predictors' segments, but NOT in the user's own segment.
3. This is essentially finding intersection of all predictor segments and subtracting the user's segment from that.

Time Complexity:
O(n log n) per test case due to sorting operations within the algorithm.
Space Complexity:
O(n) for storing input, intermediate results, and temporary arrays.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
res_test = []
for _ in range(int(input())):
    n = int(input())
    l, r = [0] * n, [0] * n
    for i in range(n):
        l[i], r[i] = map(int, input().split())
    res = [0] * n
    mx_l, mx_r = max(l), max(r)
    idx = list(range(n))
    for t in range(2):  # Two passes to handle symmetric cases
        # Sort indices by a custom key to prioritize certain order
        idx = sorted(idx, key=lambda x: (l[x] << 30) + mx_r - r[x])
        s = []
        for i in idx:
            # Stack based approach to find previous compatible interval
            while s and r[s[-1]] < r[i]:
                s.pop()
            if s:
                res[i] += l[i] - l[s[-1]]
            s.append(i)
        # Flip the segments for next pass
        for i in range(n):
            r[i], l[i] = mx_l - l[i], mx_r - r[i]
    # Adjust for duplicate intervals
    for ix in range(1, n):
        if l[idx[ix]] == l[idx[ix - 1]] and r[idx[ix]] == r[idx[ix - 1]]:
            res[idx[ix]] = res[idx[ix - 1]] = 0
    res_test.extend(res)
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/codeForces/