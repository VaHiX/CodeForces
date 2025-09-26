# Contest 2021, Problem E1: Digital Village (Easy Version)
# URL: https://codeforces.com/contest/2021/problem/E1

import sys
input = sys.stdin.readline
# Status: checked
class DSF:
    def __init__(self, n:int) -> None:
        self.par = [i for i in range(n)]
        self.siz =  [1]*n
        self.num = [0]*n
        self.sco = [0]*n
    def root(self, x: int) -> int:
        while self.par[x] != x:
            self.par[x] = self.par[self.par[x]]
            x = self.par[x]
        return x

    def union(self, x: int, y: int, v) -> bool:
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return False
        if self.siz[x] < self.siz[y]:
            x, y = y, x
        self.siz[x] += self.siz[y]
        self.par[y] = x
        xx = self.sco[x] + self.num[y] * v
        yy = self.sco[y] + self.num[x] * v
        yp = self.num[y] * v - self.sco[y]
        xp = self.num[x] * v - self.sco[x]
        self.num[x] += self.num[y]
        if xx <= yy:
            self.sco[x] = xx
            return yp
        else:
            self.sco[x] = yy
            return xp
    def same(self, x: int, y: int) -> bool:
        return self.root(x) == self.root(y)
    def size(self, x: int) -> int:
        return self.siz[self.root(x)]

for _ in range(int(input())):
    n,m,p = map(int, input().split())
    P = [int(i) - 1 for i in input().split()]
    ED = [tuple(map(int, input().split())) for i in range(m)]
    ED.sort(key=lambda x:x[2])
    dsu = DSF(n)
    for i in P: dsu.num[i] = 1
    X = []
    for a,b,c in ED:
        a-=1;b-=1
        if dsu.same(a,b): continue
        v = dsu.union(a,b,c)
        X.append(v)
    val = dsu.sco[dsu.root(0)]
    X.sort(reverse=True)
    print(val,end = " ")
    for i in X:
        val -= i
        print(val,end = " ")
    print()