# Contest 2046, Problem C: Adventurers
# URL: https://codeforces.com/contest/2046/problem/C

from sys import stdin, stderr

input = lambda: stdin.readline().strip()
from bisect import bisect_left, bisect_right

II = lambda: int(input())
MII = lambda: map(int, input().split())
LII = lambda: list(MII())


class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.a = [0] * n

    def add(self, i, v):
        i += 1
        while i <= n:
            self.a[i - 1] = self.a[i - 1] + v
            i += i & -i

    def select(self, k):
        x = 0
        cur = 0
        i = 1 << (self.n.bit_length() - 1)
        while i > 0:
            if x + i <= self.n and cur + self.a[x + i - 1] <= k:
                x += i
                cur += self.a[x - 1]
            i >>= 1
        return x


t = II()
for _ in range(t):
    n = II()
    p = []
    ys = []
    for _ in range(n):
        x, y = MII()
        p.append((x, y))
        ys.append(y)

    ys.sort()
    ys = list(set(ys))

    tr_l = FenwickTree(n)
    tr_r = FenwickTree(n)
    p.sort()
    # print("ys", *ys)
    for i, (x, y) in enumerate(p):
        y = bisect_left(ys, y)
        p[i] = (x, y)
        tr_r.add(y, 1)

    ans = 0
    pos = (0, 0)
    for i in range(n):
        x, y = p[i]
        tr_l.add(y, 1)
        tr_r.add(y, -1)
        if i < n - 1 and x == p[i + 1][0]:
            continue

        while True:
            if i + 1 < 2 * (ans + 1):
                break
            if n - 1 - i < 2 * (ans + 1):
                break

            yl = max(tr_l.select(ans), tr_r.select(ans))
            yr = min(tr_l.select(i - ans), tr_r.select((n - 1) - i - 1 - ans))
            if yl >= yr:
                break
            ans += 1
            pos = (x + 1, ys[yr])

    print(ans)
    print(*pos)
