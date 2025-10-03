# Problem: CF 2082 F - MST in Modulo Graph
# https://codeforces.com/contest/2082/problem/F

"""
F. MST in Modulo Graph

This problem involves finding the Minimum Spanning Tree (MST) of a complete graph where edge weights are defined by the modulo operation between vertex weights.

Key idea:
- For each edge connecting vertices x and y, weight = max(px, py) mod min(px, py)
- This can be interpreted as the remainder when the larger weight is divided by the smaller one.
- We use a Disjoint Set Union (DSU) structure with a modified Kruskal's algorithm approach.

The algorithm:
1. For each possible edge weight w, we process all edges with that weight in increasing order of w.
2. For every vertex u with weight p_u, we:
   - Connect it to the next higher vertex with a present weight (i.e., next_right[u+1] % u)
   - Connect it to multiples of its weight (i.e., vertices with weights j such that j is multiple of p_u)
3. These edges are added in order of increasing weights to build the MST incrementally.

Time Complexity: O(n * log(n) + n * alpha(n)) where alpha is the inverse Ackermann function (nlogn for building and iterating over edges, and n*alpha(n) for DSU operations).
Space Complexity: O(n)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def ff(u, v):
    # Pack two 20-bit integers into one 40-bit integer
    return (u << 20) | v


def fr(x):
    # Unpack two 20-bit integers from a 40-bit integer
    return (x >> 20) & 0xFFFFF, x & 0xFFFFF


class DSU:
    def __init__(self, n):
        self._parent = list(range(n))

    def find(self, x):
        parent = self._parent
        y = x
        while x != parent[x]:
            x = parent[x]
        # Path compression
        while y != x:
            parent[y], y = x, parent[y]
        return x

    def unite(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        self._parent[y] = x
        return True


def solve_case():
    _ = int(input())
    p = list(map(int, input().split()))
    mx = max(p)
    present = [0] * (mx + 1)
    for x in p:
        present[x] = 1

    # Precompute next_right[i]: smallest index where a value is present starting from i
    next_right = [mx + 1] * (mx + 1)
    for i in range(mx, -1, -1):
        next_right[i] = i if present[i] else next_right[i + 1]

    # edges[w]: list of edges with weight w
    edges = [[] for _ in range(mx + 1)]
    for i in range(mx + 1):
        if present[i]:
            # Connect to the next rightmost node that has a value > current, modulo current
            if i + 1 <= mx:
                edges[next_right[i + 1] % i].append(ff(i, next_right[i + 1]))
            # Connect to all multiples of current value (j where j = k*i for some integer k)
            for j in range(2 * i, mx + 1, i):
                edges[next_right[j] % i].append(ff(i, next_right[j]))
    
    ans = 0
    dsu = DSU(mx + 1)
    # Process all weights from 0 to mx
    for weight, edges_with_weight in enumerate(edges):
        if not edges_with_weight:
            continue
        for x in edges_with_weight:
            u, v = fr(x)
            if dsu.unite(u, v):
                ans += weight
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/