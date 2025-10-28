# Problem: CF 2073 C - Cactus Connectivity
# https://codeforces.com/contest/2073/problem/C

import sys

input = sys.stdin.readline


class UF:
    def __init__(self, n):
        self.par = list(range(n))

    def find(self, x):
        while x != self.par[x]:
            u = self.par[self.par[x]]
            self.par[x] = u
            x = u
        return x

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        self.par[a] = b


n, m = map(int, input().split())
UF = UF(2 * n)
out = 1
for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    if UF.find(u) == UF.find(v):
        continue
    out += 1
    UF.union(u, ~v)
    UF.union(~u, v)
print(out)


# https://github.com/VaHiX/CodeForces/