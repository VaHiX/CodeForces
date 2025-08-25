# Contest 2081, Problem D: MST in Modulo Graph
# URL: https://codeforces.com/contest/2081/problem/D

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
#######################################################################


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
    return (a << 40) | (b << 20) | c


def tob(x):
    y, z = divmod(x, 1 << 20)

    return *divmod(y, 1 << 20), z


inf = 10**18
for _ in range(ni()):
    n = ni()
    a = na()
    m = max(a) + 1
    f = [inf] * m
    for i in range(n):
        f[a[i]] = a[i]

    for i in range(m - 2, -1, -1):
        f[i] = min(f[i], f[i + 1])
    # print(f)
    e = []
    for i in range(1, m):
        if f[i] != i:
            continue
        if i + 1 < m:
            e.append(toa(f[i + 1] % i, i, f[i + 1]))
        for j in range(i * 2, m, i):
            if f[j] != inf:
                e.append(toa(f[j] % i, i, f[j]))
    uf = UnionFind(m)

    e = sorted(e)
    ans = 0
    # print(e)
    for x in e:
        c, i, j = tob(x)
        if uf.same(i, j):
            continue
        uf.union(i, j)
        ans += c
    print(ans)
