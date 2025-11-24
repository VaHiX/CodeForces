# Problem: CF 1896 D - Ones and Twos
# https://codeforces.com/contest/1896/problem/D

"""
Algorithm: Segment Tree with Range Min/Max Query
Purpose: Efficiently handle queries to check if a subarray sum equals a target value in an array of 1s and 2s.

Time Complexity: O((n + q) * log n) for all operations combined
Space Complexity: O(n) for the segment tree storage

The solution uses a segment tree to maintain minimum and maximum indices of 1s in the array,
which allows efficient checking of subarray sums by analyzing the possible range of sums.

Key Techniques:
- Segment tree for range queries
- Bit manipulation to optimize sum checks
- Dynamic updates with lazy propagation approach
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def update(i, x, y):
    i += l1
    tree1[i] = x
    tree2[i] = y
    i >>= 1
    while i:
        tree1[i] = min(tree1[2 * i], tree1[2 * i + 1])
        tree2[i] = max(tree2[2 * i], tree2[2 * i + 1])
        i >>= 1
    return


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n, q = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    l1 = pow(2, (n + 1).bit_length())
    l2 = 2 * l1
    tree1, tree2 = [inf] * l2, [-inf] * l2
    for i in range(1, n + 1):
        if a[i] == 1:
            tree1[i + l1], tree2[i + l1] = i, i
    for i in range(l1 - 1, 0, -1):
        tree1[i] = min(tree1[2 * i], tree1[2 * i + 1])
    for i in range(l1 - 1, 0, -1):
        tree2[i] = max(tree2[2 * i], tree2[2 * i + 1])
    now = sum(a)
    for _ in range(q):
        t = list(map(int, input().split()))
        if t[0] == 1:
            s = t[1]
            if now < s:
                ans0 = "NO"
            elif tree1[1] == inf:
                ans0 = "YES" if not s & 1 else "NO"
            else:
                l, r = tree1[1] - 1, n - tree2[1]
                c = min(l, r)
                ans0 = (
                    "NO" if now - 2 * min(l, r) <= s <= now and (now ^ s) & 1 else "YES"
                )
            ans.append(ans0)
        else:
            i, v = t[1], t[2]
            if a[i] < v:
                now += 1
                update(i, inf, -inf)
            elif a[i] > v:
                now -= 1
                update(i, i, i)
            a[i] = v
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/