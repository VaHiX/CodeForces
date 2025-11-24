# Problem: CF 1862 G - The Great Equalizer
# https://codeforces.com/contest/1862/problem/G

"""
Algorithm/Technique: Segment Tree, Coordinate Compression, Simulation
Time Complexity: O((n + q) * log(n + q)) where n is array size and q is number of operations
Space Complexity: O((n + q) * log(n + q)) for segment trees and auxiliary structures

This code simulates the "The Great Equalizer" device operation on an array.
For each query:
1. Update array element at position i with value x
2. Run the device simulation on the modified array
3. Return the final value from the device

The simulation involves:
- Sorting and removing duplicates
- Adding arithmetic progression
- Repeating until single element remains

Uses segment trees with coordinate compression to efficiently track:
- Maximum element values
- Differences between consecutive elements
- Count of elements in each compressed coordinate
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u * m + v


def update(i, x, tree):
    i += l1
    tree[i] = x
    i >>= 1
    while i:
        tree[i] = max(tree[2 * i], tree[2 * i + 1])
        i >>= 1
    return


def get_max(s, t, tree):
    s, t = s + l1, t + l1
    ans = -inf
    while s <= t:
        if s & 1:
            ans = max(ans, tree[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = max(ans, tree[t])
            t -= 1
        t >>= 1
    return ans


def left_max(r, tree):
    s, t = l1, r + l1
    while s <= t:
        if not t & 1:
            if tree[t]:
                while t < l1:
                    t = t << 1 ^ 1 if tree[t << 1 ^ 1] else t << 1
                return t ^ l1
            t -= 1
        s >>= 1
        t >>= 1
    return -1


def right_min(l, tree):
    s, t = l + l1, l2 - 1
    while s <= t:
        if s & 1:
            if tree[s]:
                while s < l1:
                    s = s << 1 if tree[s << 1] else s << 1 ^ 1
                return s ^ l1
            s += 1
        s >>= 1
        t >>= 1
    return -1


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n = int(input())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    l1 = pow(2, (n + 1).bit_length())
    l2 = 2 * l1
    tree = [0] * l2
    for i in range(1, n + 1):
        tree[i + l1] = a[i]
    for i in range(l1 - 1, 0, -1):
        tree[i] = max(tree[2 * i], tree[2 * i + 1])
    q = int(input())
    ans0 = [0] * q
    i0, x0 = [0] * q, [0] * q
    for i in range(q):
        j, x = map(int, input().split())
        i0[i], x0[i] = j, x
        update(j, x, tree)
        ans0[i] = tree[1]
    m = n + q + 1
    u = [f(a[i], i) for i in range(n + 1)] + [f(x0[i], i + n + 1) for i in range(q)]
    v = [0]
    for i in sorted(u):
        j, k = divmod(i, m)
        if v[-1] ^ j:
            v.append(j)
        if k <= n:
            a[k] = len(v) - 1
        else:
            x0[k - n - 1] = len(v) - 1
    m = len(v)
    cnt = [0] * m
    for i in a[1:]:
        cnt[i] += 1
    l1 = pow(2, (m + 1).bit_length())
    l2 = 2 * l1
    tree1 = [0] * l2
    tree2 = [0] * l2
    la = 0
    for i in range(m):
        if cnt[i]:
            tree1[i + l1] = 1
            if la:
                tree2[la + l1] = v[i] - v[la]
            la = i
    for i in range(l1 - 1, 0, -1):
        tree1[i] = max(tree1[2 * i], tree1[2 * i + 1])
    for i in range(l1 - 1, 0, -1):
        tree2[i] = max(tree2[2 * i], tree2[2 * i + 1])
    for j in range(q):
        i, x = i0[j], x0[j]
        k = a[i]
        cnt[k] -= 1
        if not cnt[k]:
            update(k, 0, tree1)
            update(k, 0, tree2)
            l0 = left_max(k - 1, tree1)
            if l0 ^ -1:
                r0 = right_min(k + 1, tree1)
                if r0 ^ -1:
                    update(l0, v[r0] - v[l0], tree2)
                else:
                    update(l0, 0, tree2)
        k = x
        cnt[k] += 1
        a[i] = x
        if cnt[k] == 1:
            l0 = left_max(k - 1, tree1)
            r0 = right_min(k + 1, tree1)
            update(k, 1, tree1)
            if l0 ^ -1:
                update(l0, v[k] - v[l0], tree2)
            if r0 ^ -1:
                update(k, v[r0] - v[k], tree2)
        ans0[j] += tree2[1]
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/