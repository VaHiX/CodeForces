# Problem: CF 1748 E - Yet Another Array Counting Problem
# https://codeforces.com/contest/1748/problem/E

"""
Algorithm: Dynamic Programming with Sparse Table and Graph Construction
Time Complexity: O(n * log(n) + n * m) 
Space Complexity: O(n * m + n * log(n))

This solution uses sparse table for range maximum queries and dynamic programming on a tree-like structure derived from the input array.
The core idea is to compute for each position the "leftmost maximum" constraint, build a graph from these constraints,
then perform DP to count valid arrays satisfying all constraints.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u * n + v


def g(u, v):
    return u * m + v


def sparse_table(a):
    table = []
    s0, l = a, 1
    table.append(s0)
    while 2 * l <= len(a):
        s = [max(s0[i], s0[i + l]) for i in range(len(s0) - l)]
        table.append(list(s))
        s0 = s
        l *= 2
    return table


def get_max(l, r, table):
    d = (r - l + 1).bit_length() - 1
    ans = max(table[d][l], table[d][r - pow2[d] + 1])
    return ans


def make_graph(n, m):
    s = [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        s[x[i] + 2] += 1
    for i in range(2, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


t = int(input())
ans = []
mod = pow(10, 9) + 7
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    ma = sparse_table([f(a[i], n - i - 1) for i in range(n)])
    q, e, p = [f(0, n - 1)], [], [-1]
    for k in range(n):
        l, r = divmod(q[k], n)
        u = n - (get_max(l, r, ma) % n) - 1
        e.append(u)
        if l ^ u:
            q.append(f(l, u - 1))
            p.append(u)
        if u ^ r:
            q.append(f(u + 1, r))
            p.append(u)
    x = [0] * (2 * (n - 1))
    for i in range(n - 1):
        x[2 * i], x[2 * i + 1] = p[i + 1], e[i + 1]
    G, s0 = make_graph(n, n - 1)
    dp = [1] * ((n + 1) * m)
    for i in range(m):
        dp[g(n, i)] = 0
    for i in e[::-1]:
        if s0[i] == s0[i + 1]:
            continue
        if s0[i + 1] - s0[i] == 1:
            l, r = G[s0[i]], n
            if l > i:
                l, r = r, l
        else:
            l, r = G[s0[i]], G[s0[i] + 1]
        cl, cr = l // n, r // n
        for j in range(m):
            cr = (cr + dp[g(r, j)]) % mod
            dp[g(i, j)] = cl * cr % mod
            cl = (cl + dp[g(l, j)]) % mod
    l, r = e[0] * m, (e[0] + 1) * m
    ans0 = sum(dp[l:r]) % mod
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/