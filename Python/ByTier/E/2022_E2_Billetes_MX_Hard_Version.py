# Problem: CF 2022 E2 - Billetes MX (Hard Version)
# https://codeforces.com/contest/2022/problem/E2

"""
E2. Billetes MX (Hard Version)

Algorithm:
- This code solves a problem involving assigning values to cells of a grid such that all subgrids maintain a specific XOR property.
- Uses Union-Find (Disjoint Set Union) with path compression and distance tracking via XOR operations to model constraints between cells.
- Time Complexity: O((n+m+k+q)*α(n+m)) where α is the inverse Ackermann function, effectively constant for practical purposes.
- Space Complexity: O(n + m)

Techniques:
- Union-Find with distance tracking using XOR (for maintaining consistency of XOR conditions).
- Modular exponentiation to compute powers of 2 modulo 10^9 + 7.

Explanation:
Each cell in the grid is treated as a node, and the constraint that four corner values of any subgrid must XOR to zero can be modeled via a Union-Find structure.
The idea is to relate nodes by using XOR distances, ensuring that constraints are satisfied when units are merged.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def get_root(s):
    w = 0
    while s ^ root[s]:  # Find root with path compression and update weight
        s, w = root[s], w ^ dist[s]
    return s, w


def unite(s, t, w):
    s, ws = get_root(s)
    t, wt = get_root(t)
    if s == t:
        return 1 if not ws ^ wt ^ w else -1  # Return 1 if conflict (inconsistent), -1 otherwise
    if rank[s] < rank[t]:
        s, t = t, s
    if rank[s] == rank[t]:
        rank[s] += 1
    root[t], dist[t] = s, dist[s] ^ ws ^ wt ^ w  # Update parent and distance to root
    return 0


t = int(input())
ans = []
mod = pow(10, 9) + 7
l = 2 * pow(10, 5) + 5
p = [1] * l
for i in range(1, l):
    p[i] = (p[i - 1] << 30) % mod  # Precompute powers of 2^30 mod (10^9 + 7)
for _ in range(t):
    n, m, k, q = map(int, input().split())
    l = n + m
    root = [i for i in range(l + 1)]
    rank = [1 for _ in range(l + 1)]
    dist = [0] * (l + 1)
    ok, u = 1, l - 1  # ok tracks validity of solution; u = number of free variables
    for _ in range(k):
        r, c, v = map(int, input().split())
        if ok:
            f = unite(r, c + n, v)  # Unite row and column node with value v
            if f == -1:
                ok = 0
            u -= f ^ 1  # Decrease free variables if not conflict
    ans0 = [0] * (q + 1)
    if ok:
        ans0[0] = p[u]  # Initial answer based on number of independent variables
    for i in range(1, q + 1):
        r, c, v = map(int, input().split())
        if ok:
            f = unite(r, c + n, v)  # Update with new value at (r,c)
            if f == -1:
                ok = 0
            u -= f ^ 1  # Adjust free variables count
        if ok:
            ans0[i] = p[u]  # Final answer for query state
    ans.append("\n".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/codeForces/