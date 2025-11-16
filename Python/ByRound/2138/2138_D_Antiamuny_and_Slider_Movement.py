# Problem: CF 2138 D - Antiamuny and Slider Movement
# https://codeforces.com/contest/2138/problem/D

"""
Algorithm: Simulation with Combinatorial Mathematics
Time Complexity: O(q^2 * log(q) + n * q^2)
Space Complexity: O(q^2)

The problem involves computing the sum of final positions for each slider over all q! permutations
of operations. The key insight is that for each slider, its final position depends on the order of
operations applied. Rather than simulating all permutations explicitly, we use combinatorial mathematics
to count how many times each operation affects the final position of a slider.

We preprocess operations and sort them by destination position. For each slider, we compute how
many permutations result in the slider ending up at a specific position, using combinations to count
valid orderings.
"""

import sys

input = sys.stdin.readline
II = lambda: int(input())
MI = lambda: map(int, input().split())
LI = lambda: [int(a) for a in input().split()]
SI = lambda: input().rstrip()
LLI = lambda n: [[int(a) for a in input().split()] for _ in range(n)]
LSI = lambda n: [input().rstrip() for _ in range(n)]
MI_1 = lambda: map(lambda x: int(x) - 1, input().split())
LI_1 = lambda: [int(a) - 1 for a in input().split()]


def graph(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[int]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b = map(int, input().split())
        a += index
        b += index
        edge[a].add(b)
        if not dir:
            edge[b].add(a)
    return edge


def graph_w(n: int, m: int, dir: bool = False, index: int = -1) -> list[set[tuple]]:
    edge = [set() for i in range(n + 1 + index)]
    for _ in range(m):
        a, b, c = map(int, input().split())
        a += index
        b += index
        edge[a].add((b, c))
        if not dir:
            edge[b].add((a, c))
    return edge


inf = 1001001001001001001
ordalp = lambda s: ord(s) - 65 if s.isupper() else ord(s) - 97
ordallalp = lambda s: ord(s) - 39 if s.isupper() else ord(s) - 97
yes = lambda: print("Yes")
no = lambda: print("No")
yn = lambda flag: print("Yes" if flag else "No")


def acc(a: list[int]):
    sa = [0] * (len(a) + 1)
    for i in range(len(a)):
        sa[i + 1] = a[i] + sa[i]
    return sa


prinf = lambda ans: print(ans if ans < 1000001001001001001 else -1)
alplow = "abcdefghijklmnopqrstuvwxyz"
alpup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alpall = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
URDL = {"U": (-1, 0), "R": (0, 1), "D": (1, 0), "L": (0, -1)}
DIR_4 = [[-1, 0], [0, 1], [1, 0], [0, -1]]
DIR_8 = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]
DIR_BISHOP = [[-1, 1], [1, 1], [1, -1], [-1, -1]]
prime60 = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59]
sys.set_int_max_str_digits(0)


from bisect import bisect_left, bisect_right
from collections import defaultdict

DD = defaultdict
BSL = bisect_left
BSR = bisect_right


mod = 10**9 + 7


class Comb:
    __slots__ = ["fac", "finv", "mod"]

    def __init__(self, lim: int, mod: int = mod):
        """
        mod : prime
        """
        self.fac = [1] * (lim + 1)
        self.finv = [1] * (lim + 1)
        self.mod = mod
        for i in range(2, lim + 1):
            self.fac[i] = self.fac[i - 1] * i % self.mod
        self.finv[lim] = pow(self.fac[lim], -1, mod)
        for i in range(lim, 2, -1):
            self.finv[i - 1] = self.finv[i] * i % self.mod

    def C(self, a, b):
        if b < 0 or a < b:
            return 0
        if a < 0:
            return 0
        return self.fac[a] * self.finv[b] % self.mod * self.finv[a - b] % self.mod

    def __call__(self, a, b):
        if b < 0 or a < b:
            return 0
        if a < 0:
            return 0
        return self.fac[a] * self.finv[b] % self.mod * self.finv[a - b] % self.mod

    def P(self, a, b):
        if b < 0 or a < b:
            return 0
        if a < 0:
            return 0
        return self.fac[a] * self.finv[a - b] % self.mod

    def H(self, a, b):
        return self.C(a + b - 1, b)

    def F(self, a):
        return self.fac[a]

    def Fi(self, a):
        return self.finv[a]


comb = Comb(10**4, mod)


def solve():
    n, m, q = MI()
    a = LI()

    qry = []
    for i in range(n):
        a[i] -= i

    for i in range(q):
        i, x = MI()
        i -= 1
        qry.append((x - i, i))
    qry.sort()

    qry.append((inf, n))

    fac = comb.fac[q]
    ans = [0] * n
    for i in range(n):
        ans[i] = i * fac % mod

    """
    5000, 5000 だよ
    すべての操作の順列に対する総和
    すべての操作は適当なclampになる
    すべてにoffsetをとりあえずつける
    
    j = i -> clamp(x, now, x)
    j < i -> clamp(?, now, x)
    i < j -> clamp(x, now, ?)
    
    判定問題にする
    a_i > x となる通り数は？
    -> もし、 r に x 未満がないとき 
        -> l に x がある or 下から a[i] 以上
    -> 最後の r  x 未満よりあとに l x 以上があるかどうか
    """
    for j in range(n):
        l = 0
        r = 0
        for t in range(q + 1):
            x, i = qry[t]
            if i <= j:
                l += 1

        tmp = 0
        p = 0
        for t in range(q + 1):

            x, i = qry[t]
            if r == 0:
                if l > 0:
                    tmp += fac * (x - p) % mod

                elif l == 0:
                    tmp += fac * max(min(a[j], x) - p, 0) % mod

            else:

                if l >= 1:
                    t1 = comb(q, l + r) * comb(l + r - 1, r) % mod
                    t1 = (
                        t1 * comb.F(q - l - r) % mod * comb.F(l) % mod * comb.F(r) % mod
                    )
                    tmp += t1 * (x - p) % mod

            if j <= i:
                r += 1
            if i <= j:
                l -= 1

            p = x
            tmp %= mod

        ans[j] += tmp
        ans[j] %= mod

    print(*ans)


t = II()
for i in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/