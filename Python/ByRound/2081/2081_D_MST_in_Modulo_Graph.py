# Problem: CF 2081 D - MST in Modulo Graph
# https://codeforces.com/contest/2081/problem/D

"""
D. MST in Modulo Graph

Purpose:
This code finds the Minimum Spanning Tree (MST) of a special graph where:
- Vertices have weights p_i
- Edge weight between vertices x and y is max(p_x, p_y) % min(p_x, p_y)
- We use a modified Union-Find with a sorting-based approach to build the MST

Algorithms/Techniques:
1. Union-Find (Disjoint Set Union) for efficient connectivity checking
2. Sparse Table for range minimum queries (not directly used but structure is included)
3. Sorting edges by weight to apply Kruskal's algorithm
4. Optimization using prefix arrays and modular arithmetic properties

Time Complexity: O(n * log(n) + n * α(n)) where α is the inverse Ackermann function
Space Complexity: O(n)

The key insight is to precompute for each value, the minimum value greater than or equal to it,
and then consider edges formed by modulus operations in a smart way.
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")


class SparseTable:
    def __init__(self, op, lst):
        self.n = len(lst)
        self.h = self.n.bit_length()
        self.op = op
        self.data = [0] * (self.n * self.h)
        for i in range(self.n):
            self.data[i] = lst[i]
        for i in range(1, self.h):
            for j in range(self.n - (1 << i) + 1):
                self.data[i * self.n + j] = op(
                    self.data[(i - 1) * self.n + j],
                    self.data[(i - 1) * self.n + j + (1 << (i - 1))],
                )

    def prod(self, l, r):
        level = (r - l).bit_length() - 1
        return self.op(
            self.data[level * self.n + l], self.data[level * self.n + r - (1 << level)]
        )


from collections import defaultdict


class UnionFind:
    def __init__(self, n):
        self.n = n
        self.parents = [-1] * n

    def find(self, x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])
            return self.parents[x]

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return
        if self.parents[x] > self.parents[y]:
            x, y = y, x
        self.parents[x] += self.parents[y]
        self.parents[y] = x

    def size(self, x):
        return -self.parents[self.find(x)]

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def members(self, x):
        root = self.find(x)
        return [i for i in range(self.n) if self.find(i) == root]

    def roots(self):
        return [i for i, x in enumerate(self.parents) if x < 0]

    def group_count(self):
        return len(self.roots())

    def all_group_members(self):
        group_members = defaultdict(list)
        for member in range(self.n):
            group_members[self.find(member)].append(member)
        return group_members

    def __str__(self):
        return "\n".join(f"{r}: {m}" for r, m in self.all_group_members().items())


def toa(a, b, c):
    # Packs three integers (a, b, c) into a single number
    return (a << 40) | (b << 20) | c


def tob(x):
    # Unpacks a number back into three integers
    y, z = divmod(x, 1 << 20)
    return *divmod(y, 1 << 20), z


inf = 10**18
for _ in range(ni()):
    n = ni()
    a = na()
    m = max(a) + 1
    f = [inf] * m
    for i in range(n):
        f[a[i]] = a[i]  # Mark where each value occurs
    for i in range(m - 2, -1, -1):  # Propagate minimums from right to left
        f[i] = min(f[i], f[i + 1])
    e = []
    for i in range(1, m):
        if f[i] != i:
            continue  # Skip if no value exists of this value
        if i + 1 < m:  # Add edge with next value's modulo
            e.append(toa(f[i + 1] % i, i, f[i + 1]))
        for j in range(i * 2, m, i): # Add edges to multiples of i
            if f[j] != inf:
                e.append(toa(f[j] % i, i, f[j]))
    uf = UnionFind(m)
    e = sorted(e)  # Sort all potential edges by weight
    ans = 0
    for x in e:  # Process each edge in order
        c, i, j = tob(x)  # Extract edge data
        if uf.same(i, j):  # Skip if already connected
            continue
        uf.union(i, j)  # Union them
        ans += c  # Add to MST weight
    print(ans)


# https://github.com/VaHiX/codeForces/