# Contest 2148, Problem G: Farmer John's Last Wish
# URL: https://codeforces.com/contest/2148/problem/G

import sys

# sys.setrecursionlimit(300005)
int1 = lambda x: int(x)-1
pDB = lambda *x: print(*x, end="\n", file=sys.stderr)
p2D = lambda x: print(*x, sep="\n", end="\n\n", file=sys.stderr)
def II(): return int(sys.stdin.readline())
def LI(): return list(map(int, sys.stdin.readline().split()))
def LLI(rows_number): return [LI() for _ in range(rows_number)]
def LI1(): return list(map(int1, sys.stdin.readline().split()))
def LLI1(rows_number): return [LI1() for _ in range(rows_number)]
def SI(): return sys.stdin.readline().rstrip()
dij = [(0, 1), (-1, 0), (0, -1), (1, 0)]
# dij = [(0, 1), (-1, 0), (0, -1), (1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
inf = -1-(-1 << 62)
# inf = -1-(-1 << 31)
# md = 10**9+7
md = 998244353

class Sieve:
    def __init__(self, n):
        self.plist = [2]
        min_prime_factor = [2, 0]*(n//2+1)
        for x in range(3, n+1, 2):
            if min_prime_factor[x] == 0:
                min_prime_factor[x] = x
                self.plist.append(x)
                if x**2 > n: continue
                for y in range(x**2, n+1, 2*x):
                    if min_prime_factor[y] == 0:
                        min_prime_factor[y] = x
        self.min_prime_factor = min_prime_factor

    def isprime(self, x):
        return self.min_prime_factor[x] == x

    def pf(self, x):
        pp, ee = [], []
        while x > 1:
            mpf = self.min_prime_factor[x]
            if pp and mpf == pp[-1]:
                ee[-1] += 1
            else:
                pp.append(mpf)
                ee.append(1)
            x //= mpf
        return pp, ee

    # unsorted
    def factor(self, a):
        ff = [1]
        pp, ee = self.pf(a)
        for p, e in zip(pp, ee):
            ff, gg = [], ff
            w = p
            for _ in range(e):
                for f in gg: ff.append(f*w)
                w *= p
            ff += gg
        return ff

sv = Sieve(200001)

from math import gcd
from collections import Counter

def solve():
    n = II()
    aa = LI()
    g = 0
    mx = 0
    cnt = Counter()
    ans = []
    for i, a in enumerate(aa):
        pp, ee = sv.pf(a)
        for p, e in zip(pp, ee):
            q = 1
            for _ in range(e):
                q *= p
                cnt[q] += 1
                if mx < cnt[q] <= i: mx = cnt[q]
        if g and a%g: mx = i
        g=gcd(g,a)
        ans.append(mx)
    print(*ans)

    # ***************************************

testnumber = II()
# testnumber = 1
for testcase in range(testnumber):
    solve()
    # print("Alice" if solve() else "Bob")
    # print("YES" if solve() else "NO")
    # print("Yes" if solve() else "No")
