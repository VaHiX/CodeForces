# Problem: CF 2021 E2 - Digital Village (Hard Version)
# https://codeforces.com/contest/2021/problem/E2

"""
E2. Digital Village (Hard Version)

This problem involves finding the minimum total latency for connecting houses requiring internet 
to servers installed in at most k houses, for each possible value of k from 1 to n.

Approach:
- Use Union-Find (DSU) with modifications to track cost of adding new edges in a spanning tree.
- For each test case, we compute the minimum total latency by choosing optimal server locations.
- Sort edges by weight and build a Minimum Spanning Tree (MST), keeping track of how much
  additional cost would be introduced if a different edge was chosen instead of a currently used one.
- The key idea is to calculate the incremental cost of increasing k from 1 up to n.

Time Complexity: O(m log m + n^2)
Space Complexity: O(n + m)

"""

import sys

input = sys.stdin.readline


class DSF:
    def __init__(self, n: int) -> None:
        self.par = [i for i in range(n)]
        self.siz = [1] * n
        self.num = [0] * n  # Number of internet-required houses in component
        self.sco = [0] * n  # Cost of connecting this component to servers

    def root(self, x: int) -> int:
        while self.par[x] != x:
            self.par[x] = self.par[self.par[x]]  # Path compression
            x = self.par[x]
        return x

    def union(self, x: int, y: int, v) -> bool:
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return False
        if self.siz[x] < self.siz[y]:
            x, y = y, x  # Union by size
        self.siz[x] += self.siz[y]
        self.par[y] = x

        # Compute cost of connecting the new component
        xx = self.sco[x] + self.num[y] * v
        yy = self.sco[y] + self.num[x] * v
        
        # Cost saved if we add y's nodes via x vs. vice versa
        yp = self.num[y] * v - self.sco[y]
        xp = self.num[x] * v - self.sco[x]

        # Update total cost and number of nodes in the merged component
        self.num[x] += self.num[y]
        if xx <= yy:
            self.sco[x] = xx  # Prefer lower cost option
            return yp  # Return cost saved by choosing x over y for expansion
        else:
            self.sco[x] = yy
            return xp

    def same(self, x: int, y: int) -> bool:
        return self.root(x) == self.root(y)

    def size(self, x: int) -> int:
        return self.siz[self.root(x)]


for _ in range(int(input())):
    n, m, p = map(int, input().split())
    P = [int(i) - 1 for i in input().split()]  # Houses requiring internet (0-indexed)
    ED = [tuple(map(int, input().split())) for i in range(m)]
    ED.sort(key=lambda x: x[2])  # Sort edges by weight
    dsu = DSF(n)
    for i in P:
        dsu.num[i] = 1  # Mark nodes that need internet
    X = []
    for a, b, c in ED:
        a -= 1
        b -= 1
        if dsu.same(a, b):
            continue
        v = dsu.union(a, b, c)
        X.append(v)  # Record the "cost gain" to add more servers later
    
    val = dsu.sco[dsu.root(0)]  # Total cost at k=n (when all connected)
    X.sort(reverse=True)  # Sort in descending order for greedy selection
    print(val, end=" ")
    for i in X:
        val -= i
        print(val, end=" ")  # Greedily remove cheapest gains
    print()


# https://github.com/VaHiX/codeForces/