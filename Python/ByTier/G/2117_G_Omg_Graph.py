# Contest 2117, Problem G: Omg Graph
# URL: https://codeforces.com/contest/2117/problem/G

# https://codeforces.com/contest/2117

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!

INF = 1 << 30


class DSU:
    def __init__(self, n):
        self._parent = list(range(n))
        self._min_weight = [INF] * n

    def find(self, x):
        parent = self._parent
        y = x
        while x != parent[x]:
            x = parent[x]
        while y != x:
            parent[y], y = x, parent[y]
        return x

    def unite(self, x, y, w):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            self._min_weight[x] = min(self._min_weight[x], w)
            return False
        else:
            self._min_weight[x] = min(self._min_weight[x], self._min_weight[y], w)
            self._parent[y] = x
            return True

    def get_min_weight(self, x):
        return self._min_weight[self.find(x)]


def solve_case():
    n, m = map(int, input().split())
    u, v, w = [0] * m, [0] * m, [0] * m
    for i in range(m):
        u[i], v[i], w[i] = map(int, input().split())
    idx = sorted(range(m), key=lambda i: w[i])

    dsu = DSU(n)
    ans = 2 * INF
    connected = False
    for i in idx:
        dsu.unite(u[i] - 1, v[i] - 1, w[i])
        connected = connected or dsu.find(0) == dsu.find(n - 1)
        if connected:
            ans = min(ans, w[i] + dsu.get_min_weight(0))
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))
