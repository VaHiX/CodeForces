# Problem: CF 1771 F - Hossam and Range Minimum Query
# https://codeforces.com/contest/1771/problem/F

"""
Problem: F. Hossam and Range Minimum Query
Algorithm: Segment Tree with Bit Manipulation
Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

This solution uses a segment tree to efficiently answer range queries about 
the minimum number that appears an odd number of times in a given range.
The implementation handles XOR-encoded queries and uses bit manipulation 
to optimize memory and processing time.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def get_min(s, t):
    s, t = s ^ l1, t ^ l1
    ans = inf
    while s <= t:
        if s & 1:
            ans = min(ans, mi[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = min(ans, mi[t])
            t -= 1
        t >>= 1
    return ans


n = int(input())
inf = pow(10, 9) + 1
a = [0] + list(map(int, input().split())) + [inf]
u = list(a)
u.sort()
s, x = set(), []
for i in range(1, n + 1):
    if u[i - 1] < u[i] < u[i + 1]:
        s.add(u[i])
    elif u[i - 1] < u[i] == u[i + 1]:
        x.append(u[i])
y = []
l1 = pow(2, (n + 1).bit_length())
l2 = 2 * l1
mi = [inf] * l2
for i in range(1, n + 1):
    if a[i] in s:
        mi[i ^ l1] = a[i]
    else:
        y.append(i)
for i in range(l1 - 1, 0, -1):
    mi[i] = min(mi[2 * i], mi[2 * i + 1])
m = len(x)
d = dict()
for i in range(m):
    d[x[i]] = i
rr = [random.randint(1, 1 << 60) for _ in range(m)]
l3 = pow(2, (m + 1).bit_length())
l4 = 2 * l3
s0 = [1] * (l4 + 3)
s0[0] = s0[1] = 0
for i in y:
    a[i] = d[a[i]]
    j = a[i] ^ l3
    while j:
        s0[j + 2] += 1
        j >>= 1
for i in range(3, l4 + 3):
    s0[i] += s0[i - 1]
tree = [0] * s0[-1]
s1 = [0] * s0[-1]
for i in y:
    j, h = a[i] ^ l3, rr[a[i]]
    while j:
        k = s0[j + 1]
        tree[k], s1[k] = tree[k - 1] ^ h, i
        s0[j + 1] += 1
        j >>= 1
u = [0] * (n + 1)
for i in range(s0[1], s0[2]):
    h = tree[i]
    for j in range(s1[i], s1[i + 1] if s1[i + 1] else n + 1):
        u[j] = h
q = int(input())
ans, ans0 = [], 0
for _ in range(q):
    a, b = map(int, input().split())
    l, r = a ^ ans0, b ^ ans0
    ans0 = get_min(l, r)
    if u[l - 1] ^ u[r]:
        i = 1
        while not i & l3:
            l0, r0 = s0[2 * i], s0[2 * i + 1]
            p = pow(2, (r0 - l0).bit_length() - 1)
            j, k = l0, l0
            while p:
                if j + p < r0 and s1[j + p] <= l - 1:
                    j += p
                if k + p < r0 and s1[k + p] <= r:
                    k += p
                p >>= 1
            i = 2 * i if tree[j] ^ tree[k] else 2 * i + 1
        ans0 = min(ans0, x[i ^ l3])
    ans0 %= inf
    ans.append(str(ans0))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/