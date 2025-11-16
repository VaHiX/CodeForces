# Problem: CF 1967 D - Long Way to be Non-decreasing
# https://codeforces.com/contest/1967/problem/D

"""
Algorithm: Graph-based approach with Euler Tour and Binary Search
Time Complexity: O(n + m * alpha(m)) where alpha is inverse Ackermann function
Space Complexity: O(n + m)

This problem requires finding the minimum number of magic tricks to make an array non-decreasing.
Each trick allows transforming elements using a fixed transformation array b. The solution uses:
1. Graph representation of transformations
2. Euler tour to process the graph efficiently
3. Binary search on answer to find minimum tricks needed
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Build adjacency list from the transformation graph
    s = [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        s[x[i] + 2] += 1
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def euler_tour():
    # Perform Euler tour on the graph to get distances and timing info
    now = list(s0)
    t1, t2, t = [0] * (m + 1), [0] * (m + 1), 1
    rr = [0] * (m + 1)
    dist = [0] * (m + 1)
    for u in range(1, m + 1):
        if r[u] == inf:
            continue
        st = [u]
        while st:
            i = st[-1]
            dist[i], rr[i] = len(st) - 1, r[u]
            if not t1[i]:
                t1[i] = t
                t += 1
            if now[i] == s0[i + 1]:
                t2[i] = t
                t += 1
                st.pop()
            else:
                st.append(G[now[i]])
                now[i] += 1
    return t1, t2, dist, rr


t = int(input())
ans = []
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
inf = pow(10, 18) + 1
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = [0] + list(map(int, input().split()))
    f = 1
    for i in range(n - 1):
        if not a[i] <= a[i + 1]:
            f = 0
    if f:
        ans0 = 0
        ans.append(ans0)
        continue
    r = [0] * (m + 1)
    cnt = [0] * (m + 1)
    for i in range(1, m + 1):
        j = i
        while not r[j]:
            r[j] = inf
            j = b[j]
        u = r[j] & 0xFFFFFF000000 if r[j] ^ inf else i << 24
        j = i
        while r[j] == inf:
            r[j] = u
            j = b[j]
        if (u >> 24) ^ i:
            continue
        k = 1
        while not r[j] & 0xFFFFFF:
            r[j] ^= k
            j = b[j]
            k += 1
        cnt[i] = k - 1
    for i in range(1, m + 1):
        cnt[i] = cnt[r[i] >> 24]
    for i in range(1, m + 1):
        if not r[i] & 0xFFFFFF:
            r[i] = inf
    l = 0
    x = [0] * (2 * m)
    for i in range(1, m + 1):
        if r[i] == inf:
            x[2 * l], x[2 * l + 1] = b[i], i
            l += 1
    G, s0 = make_graph(m, l)
    t1, t2, dist, rr = euler_tour()
    ans0, l = 0, m.bit_length()
    for i in range(l - 1, -1, -1):
        d = ans0 ^ pow2[i]
        j, v = 0, 1
        while j ^ n and v ^ (m + 1):
            u = a[j]
            c = r[v] - rr[u]
            if c < 0:
                c += cnt[u]
            if 0 <= dist[u] + c <= d:
                j += 1
            elif dist[u] - dist[v] <= d and t1[v] <= t1[u] <= t2[v]:
                j += 1
            else:
                v += 1
        if j ^ n:
            ans0 = d
    ans0 = (ans0 + 2) % (pow2[l] + 1) - 1
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/