# Problem: CF 1949 D - Funny or Scary?
# https://codeforces.com/contest/1949/problem/D

"""
Algorithm: 
This solution uses a backtracking and greedy approach to assign funny (F) or scary (S) to undecided transition videos. 
The core idea is to avoid having more than ⌈3n/4⌉ consecutive videos of the same type across any permutation of scenarios.

Approach:
1. For each undecided transition, we try assigning either F or S.
2. We identify connected components of fixed transitions using Union-Find.
3. We reduce the problem to finding a minimum set of components to cover such that no component has more than ⌈3n/4⌉ consecutive videos of same type.
4. We greedily assign F or S based on component coverage.

Time Complexity: O(n^2 * 2^k) where k is the number of undecided edges (at most n^2/2).
Space Complexity: O(n^2) for graph representation and Union-Find structures.

Techniques:
- Union-Find for connectivity
- Backtracking with pruning
- Greedy component selection
"""

import sys


class UnionFind:
    def __init__(self, n):
        self.par = list(range(n))  # Parent array for Union-Find
        self.size = [1] * n        # Size of each component

    def find(self, x):
        while self.par[x] != x:
            x = self.par[x]
        return x

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)

        if a == b:
            return

        self.par[b] = a
        self.size[a] += self.size[b]


n = int(input())
board = [list(input().strip()) for _ in range(n)]


def mc(e, cost):
    # This function computes minimum cost to cover edges using backtracking
    if e == []:
        return ([], 0)

    u, v = e[0]
    eu = [t for t in e if u not in t]
    ev = [t for t in e if v not in t]

    lu, su = mc(eu, cost)
    lv, sv = mc(ev, cost)

    if su + cost[u] < sv + cost[v]:
        return ([u] + lu, su + cost[u])
    else:
        return ([v] + lv, sv + cost[v])


max_e = (3 * n + 3) // 4   # Maximum allowed consecutive same type videos
max_size = max_e + 1

lo = n - max_size          # Lower bound for coverage
hi = max_e // 2            # Upper bound for coverage


def att(s, f):
    # Try assigning 's' to fixed edges and 'f' to undecided edges
    edges = []

    UF = UnionFind(n)
    for i in range(n):
        for j in range(i + 1, n):
            if board[i][j] == s:
                UF.union(i, j)   # Union fixed 's' edges
            elif board[i][j] == f:
                edges.append((i, j))  # Collect undecided edges
            else:
                assert board[i][j] == "?"  # Undecided edges

    assert len(edges) <= 12    # Max number of undecided edges

    reduced = [(UF.find(u), UF.find(v)) for (u, v) in edges]  # Group by connected components

    cover, cost = mc(reduced, UF.size)  # Find minimum cost to cover components

    if cost > hi:
        return

    rem = [i for i in range(n) if UF.find(i) == i]  # Remaining connected components
    rem.sort(key=lambda x: -UF.size[x])             # Sort by size descending

    for u in rem:
        if u not in cover and cost + UF.size[u] <= hi:
            cover.append(u)
            cost += UF.size[u]

    assert cost <= hi
    if cost < lo:
        return

    full_cover = []
    for i in range(n):
        if UF.find(i) in cover:
            full_cover.append(i)

    assert len(full_cover) == cost

    for i in range(n):
        l = ""
        for j in range(n):
            if i == j:
                l += "."
                continue

            if i in full_cover and j in full_cover:
                if board[i][j] == "?":
                    l += f
                else:
                    assert board[i][j] in s + f
                    l += board[i][j]
            elif i in full_cover or j in full_cover:
                assert board[i][j] != s
                l += f
            else:
                assert board[i][j] != f
                l += s

            assert len(l) == j + 1
            assert board[i][j] == "?" or board[i][j] == l[j]
        print(l)
    sys.exit()


att("F", "S")   # Try first assigning F as fixed, S as undecided
att("S", "F")   # Try the reverse

while True:
    pass   # Infinite loop as solution is already found and terminated


# https://github.com/VaHiX/CodeForces/