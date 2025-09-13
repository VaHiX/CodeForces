# Contest 2082, Problem F: MST in Modulo Graph
# URL: https://codeforces.com/contest/2082/problem/F

# https://codeforces.com/contest/2082

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def ff(u, v):
    return (u << 20) | v


def fr(x):
    return (x >> 20) & 0xFFFFF, x & 0xFFFFF


class DSU:
    def __init__(self, n):
        self._parent = list(range(n))

    def find(self, x):
        parent = self._parent
        y = x
        while x != parent[x]:
            x = parent[x]
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
    next_right = [mx + 1] * (mx + 1)
    for i in range(mx, -1, -1):
        next_right[i] = i if present[i] else next_right[i + 1]

    edges = [[] for _ in range(mx + 1)]
    for i in range(mx + 1):
        if present[i]:
            if i + 1 <= mx:
                edges[next_right[i + 1] % i].append(ff(i, next_right[i + 1]))
            for j in range(2 * i, mx + 1, i):
                edges[next_right[j] % i].append(ff(i, next_right[j]))

    ans = 0
    dsu = DSU(mx + 1)
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
