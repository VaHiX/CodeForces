# Problem: CF 2097 B - Baggage Claim
# https://codeforces.com/contest/2097/problem/B

"""
B. Baggage Claim

This problem involves reconstructing a path on an n×m grid that visits k+1 specific odd-indexed cells,
such that the path is simple and consists of adjacent cells only.

The approach uses Union-Find (DSU) to group connected segments of the path.
For each pair of consecutive odd-indexed cells, we compute which intermediate cells must be chosen,
and connect those segments using Union-Find.
Additionally, we track:
- Number of edges in a component (e)
- Whether a component contains a cycle (loop)

Time Complexity: O(k * α(n*m)) where α is the inverse Ackermann function
Space Complexity: O(n * m)

Algorithms/Techniques:
1. Union-Find with path compression and union by size
2. Graph connectivity analysis
3. Path reconstruction logic based on movement between cells

"""

import sys
from collections import defaultdict
from types import GeneratorType
from typing import List

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))
fmax = lambda x, y: x if x > y else y


def bootstrap(f, stack=None):
    if stack is None:
        stack = []
    if stack:
        return f(*stack)
    try:
        while True:
            stack.append(next(f))
    except StopIteration:
        pass
    return f


class DSU:
    def __init__(self, n):
        self.f = list(range(n))
        self.siz = [1] * n

    def find(self, x):
        x = self.f[x]
        x_copy = x
        while x != self.f[x]:
            x = self.f[x]
        while x_copy != x:
            self.f[x_copy], x_copy = x, self.f[x_copy]
        return x

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        self.siz[x] += self.siz[y]
        self.f[y] = x
        return True

    def size(self, x):
        return self.siz[self.find(x)]


def cf1363C():
    n, m, k = mint()
    x = [0] * (k + 1)
    y = [0] * (k + 1)
    for i in range(k + 1):
        x[i], y[i] = mint()
        x[i] -= 1
        y[i] -= 1
    dsu = DSU(n * m)
    loop = [0] * (n * m)   # Whether component contains a cycle
    e = [0] * (n * m)      # Number of edges in component
    for i in range(k + 1):
        u = x[i] * m + y[i]
        loop[u] = 1
        e[u] += 1

    # Check if all consecutive pairs are connected with Manhattan distance of 2
    for i in range(1, k + 1):
        if abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]) != 2:
            print(0)
            return

        # Compute midpoint between two consecutive points
        a, b, c, d = 0, 0, 0, 0
        if x[i] == x[i - 1]:
            a = x[i]
            b = (y[i] + y[i - 1]) // 2
            c = a
            d = b
        elif y[i] == y[i - 1]:
            a = (x[i] + x[i - 1]) // 2
            b = y[i]
            c = a
            d = b
        else:
            # Diagonal case: fill in the corner points such that adjacent cells are part of path
            a = x[i]
            b = y[i - 1]
            c = x[i - 1]
            d = y[i]

        u = a * m + b
        v = c * m + d

        # If not already connected, merge components
        if not dsu.same(u, v):
            root_u = dsu.find(u)
            root_v = dsu.find(v)
            e[root_u] += e[root_v]
            loop[root_u] |= loop[root_v]
            dsu.merge(u, v)
            
        root = dsu.find(u)
        e[root] += 1
        # Special case if u == v (loop formation)
        if u == v:
            loop[root] = 1

    ans = 1
    MOD = 10**9 + 7
    for i in range(n * m):
        if dsu.find(i) == i:
            s = dsu.size(i)
            # If number of edges > nodes, impossible to build a valid path
            if e[i] > s:
                ans = 0
            elif e[i] == s:
                # No extra edges; possibly cycle or line (2 options if no cycle)
                if not loop[i]:
                    ans = (ans * 2) % MOD
            else:
                # Underdetermined case, can place in s ways
                ans = (ans * s) % MOD

    print(ans)
    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf1363C()


# https://github.com/VaHiX/codeForces/