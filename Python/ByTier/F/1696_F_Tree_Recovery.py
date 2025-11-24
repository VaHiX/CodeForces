# Problem: CF 1696 F - Tree Recovery
# https://codeforces.com/contest/1696/problem/F

"""
Tree Recovery
Algorithms/Techniques: Disjoint Set Union (DSU), Lowest Common Ancestor (LCA), BFS

Time Complexity: O(n^3 * α(n)) where α(n) is the inverse Ackermann function, due to DSU operations
Space Complexity: O(n^2) for storing the distance relationships and graph structures

This solution attempts to reconstruct a tree given distance relationships between triplets of vertices.
It uses DSU to group vertices that are equidistant from a common vertex,
then tests each valid grouping to see if it represents a valid tree structure using LCA and BFS.
"""

import sys

input = sys.stdin.readline


class DSF:
    def __init__(self, n: int) -> None:
        self.par = [i for i in range(n)]
        self.siz = [0] * n

    def root(self, x: int) -> int:
        while self.par[x] != x:
            self.par[x] = self.par[self.par[x]]  # Path compression
            x = self.par[x]
        return x

    def union(self, x: int, y: int) -> bool:
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return False
        if self.siz[x] < self.siz[y]:
            x, y = y, x
        self.siz[x] += self.siz[y]
        self.par[y] = x
        return True

    def same(self, x: int, y: int) -> bool:
        return self.root(x) == self.root(y)

    def size(self, x: int) -> int:
        return self.siz[self.root(x)]


class LCA:
    def __init__(self, n, graph, root=0):

        self.n = n
        path = [-1] * (n - 1)
        nodein = [-1] * n
        par = [-1] * n
        curtime = -1
        todo = [root]
        while todo:
            v = todo.pop()
            path[curtime] = par[v]
            curtime += 1
            nodein[v] = curtime
            for u in graph[v]:
                if nodein[u] == -1:
                    par[u] = v
                    todo.append(u)

        a = [nodein[v] for v in path]
        m = len(a)
        log = m.bit_length() - 1
        self.data = [a] + [[] for i in range(log)]
        for i in range(log):
            pre = self.data[i]
            l = 1 << i
            self.data[i + 1] = [
                pre[j] if pre[j] < pre[j + l] else pre[j + l]
                for j in range(len(pre) - l)
            ]

        self.path = path
        self.nodein = nodein

    def lca(self, u, v):
        if u == v:
            return u
        l, r = self.nodein[u], self.nodein[v]
        if l > r:
            l, r = r, l
        u = (r - l).bit_length() - 1
        return self.path[
            (
                self.data[u][l]
                if self.data[u][l] < self.data[u][r - (1 << u)]
                else self.data[u][r - (1 << u)]
            )
        ]


for _ in range(int(input())):
    n = int(input())
    dsu = DSF(n * n)
    A = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
    tries = 0
    for i in range(n - 1):
        v = input().split()
        for j in range(i + 1, n):
            s = v[j - 1 - i]
            for k in range(n):
                if s[k] == "1":
                    A[i][j][k] = 1
                    dsu.union(i + k * n, j + k * n)
    F = [[] for _ in range(n * n)]
    for i in range(n):
        for j in range(i + 1, n):
            dsu.union(i + j * n, j + i * n)
    for i in range(n):
        for j in range(i + 1, n):
            F[dsu.root(i + j * n)].append((i, j))
    for i in range(n * n):
        if tries > 3:  # Limit attempts to avoid timeout
            print("No")
            break
        if len(F[i]) == n - 1:
            tries += 1
            edg = list(F[i])
            OK = [0 for _ in range(n)]
            for a, b in edg:
                OK[a] = 1
                OK[b] = 1
            if min(OK) == 0:
                continue
            G = [[] for _ in range(n)]
            for a, b in edg:
                G[a].append(b)
                G[b].append(a)
            lca = LCA(n, G, 0)
            D = [0 for _ in range(n)]
            P = [-1 for _ in range(n)]
            q = [0]
            for i in q:
                for c in G[i]:
                    if P[i] == c:
                        continue
                    P[c] = i
                    D[c] = D[i] + 1
                    q.append(c)
            DI = [[0 for _ in range(n)] for _ in range(n)]
            for a in range(n):
                for b in range(n):
                    DI[a][b] = D[a] + D[b] - 2 * D[lca.lca(a, b)]
            ok = 1
            for i in range(n):
                for j in range(i + 1, n):
                    for k in range(n):
                        if A[i][j][k] ^ (DI[i][k] == DI[j][k]):  # Check validity of distance relationships
                            ok = 0
            if ok:
                print("Yes")
                for a, b in edg:
                    print(a + 1, b + 1)
            else:
                continue
            break
    else:
        print("No")


# https://github.com/VaHiX/CodeForces/