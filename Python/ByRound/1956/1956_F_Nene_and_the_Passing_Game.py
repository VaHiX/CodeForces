# Problem: CF 1956 F - Nene and the Passing Game
# https://codeforces.com/contest/1956/problem/F

"""
Algorithm: Union-Find with Interval Merging Technique
Time Complexity: O(n log n) due to sorting and union-find operations
Space Complexity: O(n) for storing intervals and union-find structures

This problem involves finding the minimum number of rounds to ensure each player 
can be part of at least one sequence of passes, where a pass is valid if 
|player_i - player_j| is within [l_i + l_j, r_i + r_j].

The solution uses a sweep-line approach with coordinate compression and union-find:
1. Convert intervals to events for coordinate compression
2. Use sweep line to determine which players can reach each other
3. Union players that can connect via valid passes
4. Count number of connected components (rounds needed)
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 24 ^ v


def get_root(s):
    v = []
    while not s == root[s]:
        v.append(s)
        s = root[s]
    for i in v:
        root[i] = s
    return s


def unite(s, t):
    s, t = get_root(s), get_root(t)
    if s == t:
        return
    if rank[s] < rank[t]:
        s, t = t, s
    if rank[s] == rank[t]:
        rank[s] += 1
    root[t] = s
    return


def same(s, t):
    return True if get_root(s) == get_root(t) else False


t = int(input())
ans = []
inf = pow(10, 15) + 1
for _ in range(t):
    n = int(input())
    x, y, ma0 = [0] * (2 * n), [0] * (2 * n), [0] * (2 * n)
    n3 = 3 * n
    for i in range(n):
        l, r = map(int, input().split())
        # Encode events for sweep line
        x[2 * i], x[2 * i + 1] = f(l + i + n3, 2 * i), f(-l + i + n3, 2 * i + 1)
        y[2 * i], y[2 * i + 1] = f(-r - i + n3, 2 * i), f(r - i + n3, 2 * i + 1)
    x.sort()
    y.sort()
    # Extract original indices from encoded values
    for i in range(2 * n):
        x[i] &= 0xFFFFFF
        y[i] &= 0xFFFFFF
    p = [0] * (2 * n)
    root = [i for i in range(n)]
    rank = [1 for _ in range(n)]
    c = 0
    # Process y events to build prefix max array
    for i in y:
        if not i & 1:
            c += 1
        p[i] = c
    ma = -inf
    # Process x events from right to left
    for i in range(2 * n - 1, -1, -1):
        j = x[i]
        if j & 1:
            ma = max(ma, p[j])
        else:
            ma0[i] = ma
    mi, k = inf, -1
    # Final processing step to unite players
    for i, ma in zip(x, ma0):
        pi = p[i]
        if not i & 1:
            if mi >= pi:
                if k ^ -1 and ma >= mi:
                    unite(i >> 1, k >> 1)
                mi, k = pi, i
            if ma >= pi:
                unite(i >> 1, k >> 1)
        elif mi <= pi:
            unite(i >> 1, k >> 1)
    ans0 = 0
    # Count number of connected components
    for i in range(n):
        if get_root(i) == i:
            ans0 += 1
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/