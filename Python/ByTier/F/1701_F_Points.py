# Problem: CF 1701 F - Points
# https://codeforces.com/contest/1701/problem/F

"""
Code Purpose:
This code solves the problem of maintaining a dynamic set of points on a coordinate line and
answering queries about the number of "beautiful" triples. A triple (i,j,k) is beautiful if i < j < k and k - i <= d.
The solution uses a combination of a Fenwick tree for point counting and a segmented approach with lazy propagation
to efficiently handle updates and queries.

Algorithms/Techniques:
- Fenwick Tree (Binary Indexed Tree) for efficient point counting and prefix sum queries.
- Segmented updates with lazy propagation to handle range updates efficiently.
- Coordinate compression and bucketing to reduce memory usage and improve performance.

Time Complexity:
- Each query operation (add/remove point and count triples) takes O(log n + sqrt(d)) time.
- Total time complexity is O(q * (log n + sqrt(d))) where q is the number of queries.

Space Complexity:
- O(n * m) where n is the maximum coordinate value and m is a block size.
- Space complexity is O(n * m) due to the segmented array and Fenwick tree.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def fenwick_tree(n):
    tree = [0] * (n + 1)
    return tree


def get_sum0(i):
    s = 0
    while i > 0:
        s += tree[i]
        i -= i & -i
    return s


def get_sum(s, t):
    ans = 0 if s > t else get_sum0(t) - get_sum0(s - 1)
    return ans


def add(i, x):
    while i < len(tree):
        tree[i] += x
        i += i & -i


def f(i):
    if not lazy[i]:
        return
    li = lazy[i]
    for j in range(i * m, (i + 1) * m):
        if now[j]:
            x[j] += li
    lazy[i] = 0
    return


p, d = map(int, input().split())
a = list(map(int, input().split()))
m = 888
n = (2 * pow(10, 5) + m) // m + 1
tree = fenwick_tree(n * m)
now = [0] * (n * m)
cnt = [0] * n
x, y = [0] * (n * m), [0] * n
lazy = [0] * n
ans = []
ans0 = 0
for i in a:
    l, r = i + 1, min(n * m - 1, i + d)
    c0 = get_sum(l, r)
    c = c0 * (c0 - 1) // 2
    l, r = max(0, i - d), i - 1
    l0, r0 = l // m, r // m
    f(l0)
    f(i // m)
    if not now[i]:
        y[i // m] += c0
        cnt[i // m] += 1
        x[i] = c0
        while l <= r and l % m:
            if now[l]:
                c += x[l]
                x[l] += 1
                y[l0] += 1
            l += 1
        l0 = l // m
        while l + m - 1 <= r:
            c += y[l0]
            y[l0] += cnt[l0]
            lazy[l0] += 1
            l0 += 1
            l += m
        while l <= r:
            if now[l]:
                c += x[l]
                x[l] += 1
                y[l0] += 1
            l += 1
        ans0 += c
        add(i, 1)
    else:
        y[i // m] -= c0
        cnt[i // m] -= 1
        x[i] = 0
        while l <= r and l % m:
            if now[l]:
                x[l] -= 1
                y[l0] -= 1
                c += x[l]
            l += 1
        l0 = l // m
        while l + m - 1 <= r:
            y[l0] -= cnt[l0]
            lazy[l0] -= 1
            c += y[l0]
            l0 += 1
            l += m
        while l <= r:
            if now[l]:
                x[l] -= 1
                y[l0] -= 1
                c += x[l]
            l += 1
        ans0 -= c
        add(i, -1)
    now[i] ^= 1
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/