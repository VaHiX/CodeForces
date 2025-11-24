# Problem: CF 1878 G - wxhtzdy ORO Tree
# https://codeforces.com/contest/1878/problem/G

"""
Algorithm: Tree LCA with Bitwise OR preprocessing for queries
- Preprocess tree with binary lifting and OR values
- For each query, find LCA and check all relevant vertices on path
- Calculate maximum niceness using bitwise OR and bit count operations

Time Complexity: O(n * log n + q * log n * 30) 
Space Complexity: O(n * log n)

Where n is the number of vertices and q is the number of queries.
"""
import random
import sys

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)


class LCA:
    def __init__(self, n, edges, a):
        self.a = a
        self.n = n
        self.adj = edges
        self.depth = [0] * n
        self.parent = [-1] * (Max_bit * n)
        self.or_ = [0] * (Max_bit * n)
        self.bits_first = [-1] * (30 * n)

        self.bfs()
        for j in range(1, Max_bit):
            for i in range(n):
                p = self.parent[self.f(i, j - 1)]
                if p != -1:
                    self.parent[self.f(i, j)] = self.parent[self.f(p, j - 1)]
                    self.or_[self.f(i, j)] = (
                        self.or_[self.f(i, j - 1)] | self.or_[self.f(p, j - 1)]
                    )

    def f(self, u, v):
        return self.n * v + u

    def bfs(self):
        from collections import deque

        q = deque([0])
        d = 0
        while q:
            for _ in range(len(q)):
                T = q.popleft()
                u = T // self.n
                p = T % self.n
                for bit in range(30):
                    if self.a[u] & (1 << bit):
                        self.bits_first[self.f(u, bit)] = u
                    else:
                        self.bits_first[self.f(u, bit)] = self.bits_first[
                            self.f(p, bit)
                        ]
                self.parent[self.f(u, 0)] = p
                self.or_[self.f(u, 0)] = self.a[p]
                self.depth[u] = d
                for v in self.adj[u]:
                    if v != p:
                        q.append(v * self.n + u)
            d += 1

    def lca(self, u, v):
        if self.depth[u] < self.depth[v]:
            u, v = v, u
        for j in range(Max_bit - 1, -1, -1):
            if self.depth[u] - (1 << j) >= self.depth[v]:
                u = self.parent[self.f(u, j)]
        if u == v:
            return u
        for j in range(Max_bit - 1, -1, -1):
            if self.parent[self.f(u, j)] != self.parent[self.f(v, j)]:
                u = self.parent[self.f(u, j)]
                v = self.parent[self.f(v, j)]
        return self.parent[self.f(u, 0)]

    def in_(self, x, y):
        return self.depth[x] <= self.depth[y]

    def OR(self, u, dis):
        res = self.a[u]
        while dis > 0:
            lb = dis & -dis
            res |= self.or_[self.f(u, pow2[lb])]
            u = self.parent[self.f(u, pow2[lb])]
            dis -= lb
        return res

    def query(self, u, v, lca):
        return self.OR(u, self.depth[u] - self.depth[lca]) | self.OR(
            v, self.depth[v] - self.depth[lca]
        )


def popcount64(x):
    x = x - ((x >> 1) & 0x5555555555555555)
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333)
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F
    x = x + (x >> 8)
    x = x + (x >> 16)
    x = x + (x >> 32)
    return x & 0x7F


p2 = [1]
pow2 = {1: 0}
for i in range(20):
    pow2[p2[-1] * 2] = i + 1
    p2.append(p2[-1] * 2)
t = int(input())
for _ in range(t):
    n = int(input())
    for i in range(21):
        if n >= p2[i]:
            Max_bit = i + 1
    a = list(map(int, input().split()))
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)
    tree = LCA(n, g, a)
    q = int(input())
    ans = []
    for _ in range(q):
        x, y = map(int, input().split())
        x -= 1
        y -= 1
        lca = tree.lca(x, y)
        temp_x = set()
        temp_y = set()
        for bit in range(30):
            first = tree.bits_first[tree.f(x, bit)]
            if first != -1 and tree.in_(lca, first):
                temp_x.add(first)
            first = tree.bits_first[tree.f(y, bit)]
            if first != -1 and tree.in_(lca, first):
                temp_y.add(first)
        res = 0
        for point in temp_x:
            x1 = tree.query(x, point, point)
            x2 = tree.query(y, point, lca)
            res = max(res, popcount64(x1) + popcount64(x2))
        for point in temp_y:
            x1 = tree.query(x, point, lca)
            x2 = tree.query(y, point, point)
            res = max(res, popcount64(x1) + popcount64(x2))
        ans.append(res)
    print(*ans)


# https://github.com/VaHiX/CodeForces/