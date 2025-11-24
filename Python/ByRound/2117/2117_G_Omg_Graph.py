# Problem: CF 2117 G - Omg Graph
# https://codeforces.com/contest/2117/problem/G

"""
G. Omg Graph

Purpose:
This code solves the problem of finding the minimum cost path from vertex 1 to vertex n in an undirected connected weighted graph. 
The cost of a path is defined as the sum of the minimum and maximum edge weights along that path.
It uses a Union-Find (DSU) data structure with modifications to track minimum edge weights in connected components.

Algorithm:
- Sort edges by weight in ascending order
- Use DSU to gradually build a spanning tree-like structure, keeping track of min edge weight in each component
- For each edge added, check if nodes 1 and n are connected
- If they are connected, calculate the cost as current edge weight + minimum edge weight of the component containing 1 and n
- Return the minimum such cost across all edges

Time Complexity:
O(m * α(n)) where α is the inverse Ackermann function (nearly constant)
Space Complexity:
O(n + m) for DSU structure and input storage

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
INF = 1 << 30


class DSU:
    def __init__(self, n):
        self._parent = list(range(n))       # Parent array for DSU
        self._min_weight = [INF] * n        # Min weight in each component

    def find(self, x):
        parent = self._parent
        y = x
        while x != parent[x]:
            x = parent[x]
        while y != x:
            parent[y], y = x, parent[y]     # Path compression
        return x

    def unite(self, x, y, w):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            self._min_weight[x] = min(self._min_weight[x], w)
            return False
        else:
            self._min_weight[x] = min(self._min_weight[x], self._min_weight[y], w)
            self._parent[y] = x             # Union operation
            return True

    def get_min_weight(self, x):
        return self._min_weight[self.find(x)]


def solve_case():
    n, m = map(int, input().split())
    u, v, w = [0] * m, [0] * m, [0] * m
    for i in range(m):
        u[i], v[i], w[i] = map(int, input().split())
    idx = sorted(range(m), key=lambda i: w[i])  # Sort edges by weight
    dsu = DSU(n)
    ans = 2 * INF
    connected = False
    for i in idx:
        dsu.unite(u[i] - 1, v[i] - 1, w[i])
        connected = connected or dsu.find(0) == dsu.find(n - 1)  # Check if 1 and n are connected
        if connected:
            ans = min(ans, w[i] + dsu.get_min_weight(0))  # Calculate cost for current edge
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/