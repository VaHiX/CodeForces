# Problem: CF 1763 F - Edge Queries
# https://codeforces.com/contest/1763/problem/F

# Flowerbox for code description
"""
Problem: Edge Queries
Algorithm: Tarjan's Algorithm for finding biconnected components, DFS for preprocessing, LCA for querying
Time Complexity: O(n + m + q * log(n)) where n is number of nodes, m is number of edges, q is number of queries
Space Complexity: O(n + m) for storing graph and additional data structures

This solution uses:
1. Tarjan's algorithm to decompose the graph into biconnected components
2. Preprocessing with DFS and binary lifting to answer LCA queries efficiently
3. For each query (a, b), computes the number of edges on all simple paths from a to b that are not bridges
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 4096
inf = float("inf")


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


n, m = MII()
path = [[] for _ in range(n)]
new_path = [[] for _ in range(2 * n)]
edges = []
for _ in range(m):
    x, y = GMI()
    path[x].append(y)
    path[y].append(x)
    edges.append([x, y])

stack = []
tmstamp = 0
node = n
dfn = [0] * n
low = [0] * n
col = [0] * n
pre = [0] * (n * 2)
depth = [0] * (n * 2)


@bootstrap
def tarjan(u, f):
    global tmstamp, node
    tmstamp += 1
    dfn[u] = low[u] = tmstamp
    stack.append(u)
    for v in path[u]:
        if dfn[v] == 0:
            yield tarjan(v, u)
            low[u] = min(low[u], low[v])
        elif v != f:
            low[u] = min(low[u], dfn[v])
    if low[u] == dfn[u]:
        # Found a biconnected component
        while True:
            col[stack[-1]] = node
            new_path[stack[-1]].append(node)
            new_path[node].append(stack[-1])
            tmp = stack.pop()
            if tmp == u:
                break
        node += 1
    yield


tarjan(0, -1)
for x, y in edges:
    if col[x] == col[y]:
        # If both ends belong to same biconnected component, increment pre value
        pre[col[x]] += 1
    else:
        # Otherwise connect nodes in the new_path (graph of biconnected components)
        new_path[x].append(y)
        new_path[y].append(x)

father = [[-1] * 19 for _ in range(2 * n)]


@bootstrap
def dfs(u, f):
    depth[u] = depth[f] + 1
    if f != -1:
        pre[u] += pre[f]  # Propagate the pre counts
    father[u][0] = f
    tmp = f
    for i in range(1, 19):
        if tmp == -1:
            break
        father[u][i] = father[tmp][i - 1]
        tmp = father[u][i]
    for v in new_path[u]:
        if v != f:
            yield dfs(v, u)
    yield


dfs(0, -1)


def lca(u, v):
    # Lowest Common Ancestor finder with binary lifting
    if u == v:
        return u
    if depth[u] < depth[v]:
        u, v = v, u
    delta = depth[u] - depth[v]
    for i in range(19):
        if delta & (1 << i):
            u = father[u][i]
    if u == v:
        return u
    for i in range(18, -1, -1):
        if father[u][i] != father[v][i]:
            u = father[u][i]
            v = father[v][i]
    return father[u][0]


q = II()
for _ in range(q):
    x, y = GMI()
    tmp = lca(x, y)
    # Calculate the number of edges that are on any path from a to b
    # The key idea is compute sum of pre values (edge counts in the subtree)
    # subtracting the contributions of lowest common ancestor and its parent
    if father[tmp][0] != -1:
        print(pre[x] + pre[y] - pre[tmp] - pre[father[tmp][0]])
    else:
        print(pre[x] + pre[y] - pre[tmp])


# https://github.com/VaHiX/CodeForces/