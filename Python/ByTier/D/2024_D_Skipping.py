# Contest 2024, Problem D: Skipping
# URL: https://codeforces.com/contest/2024/problem/D

from sys import stdin
input = lambda: stdin.buffer.readline().decode().strip()
from math import inf


class Fenwick:
    def __init__(self, n, func=min):
        self.n = n + 1
        self.tree = [inf]*self.n
        self.func = func

    def query(self, i):
        x = inf
        while i > 0:
            x = self.func(self.tree[i], x)
            i -= i & -i
        return x
    
    def update(self, i, x):
        while i < self.n:
            self.tree[i] = self.func(x, self.tree[i])
            i += i & -i


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    pre = ans = 0
    cost = Fenwick(n)
    cost.update(n, 0)   # reversed

    for i in range(n):
        pre += a[i]
        c = cost.query(n-i)
        cost.update(n-b[i]+1, c + a[i])
        ans = max(ans, pre - c)

    print(ans)