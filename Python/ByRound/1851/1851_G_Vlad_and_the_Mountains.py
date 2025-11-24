# Problem: CF 1851 G - Vlad and the Mountains
# https://codeforces.com/contest/1851/problem/G

"""
Algorithm: Union-Find (Disjoint Set Union) with offline query processing
Time Complexity: O((n + m + q) * α(n)) where α is the inverse Ackermann function
Space Complexity: O(n + m + q)

This solution uses a technique called "coordinate compression" combined with a 
disjoint set union (DSU) to determine if there's a path between two nodes with 
sufficient energy. The key insight is to sort edges by their maximum height and 
queries by the maximum reachable height (initial height + energy). Then process 
edges incrementally and check if start and end nodes are connected.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class DisjointSetUnion:
    def __init__(self, n):
        self.n = n
        self.parent = list(range(n))

    def find_set(self, x):
        """Finds the representative of the set that x belongs to."""
        assert 0 <= x < self.n
        xx = x
        while x != self.parent[x]:
            x = self.parent[x]
        while xx != x:
            self.parent[xx], xx = x, self.parent[xx]
        return x

    def same_set(self, x, y):
        """Returns true if x and y belong to the same set, and false otherwise."""
        assert 0 <= x < self.n and 0 <= y < self.n
        return self.find_set(x) == self.find_set(y)

    def unite_sets(self, x, y):
        """Unites two sets; returns True if the sets were not united before and False otherwise."""
        assert 0 <= x < self.n and 0 <= y < self.n
        x, y = self.find_set(x), self.find_set(y)
        if x == y:
            return False
        else:
            self.parent[y] = x
            return True


def solve_case():
    n, m = map(int, input().split())
    h = list(map(int, input().split()))
    edges = []
    # For each edge, store the two nodes and the maximum height of the two nodes
    for _ in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        edges += [(u, v, max(h[u], h[v]))]

    q = int(input())
    a, b, max_h = [0] * q, [0] * q, [0] * q
    # For each query, precompute the maximum reachable height (initial height + energy)
    for i in range(q):
        aa, bb, ee = map(int, input().split())
        a[i] = aa - 1
        b[i] = bb - 1
        max_h[i] = h[a[i]] + ee

    # Sort edges by their maximum height (for processing in order)
    edge_idx = sorted(range(m), key=lambda x: edges[x][2])
    # Sort queries by their maximum reachable height (for processing in order)
    query_idx = sorted(range(q), key=lambda x: max_h[x])

    ans = ["NO"] * q
    dsu = DisjointSetUnion(n)
    eidx = 0

    # Process queries in order of increasing maximum reachable height
    for qidx in query_idx:
        # Add all edges whose maximum height is less than or equal to the query's max height
        while eidx < m and edges[edge_idx[eidx]][2] <= max_h[qidx]:
            dsu.unite_sets(edges[edge_idx[eidx]][0], edges[edge_idx[eidx]][1])
            eidx += 1
        # Check if start and end nodes are connected in DSU
        if dsu.same_set(a[qidx], b[qidx]):
            ans[qidx] = "YES"

    sys.stdout.write("\n".join(ans))
    sys.stdout.write("\n")


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/CodeForces/