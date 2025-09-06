# Contest 2097, Problem B: Baggage Claim
# URL: https://codeforces.com/contest/2097/problem/B

import sys
import re

from array import array

# region fastio
from collections import Counter, deque
from heapq import heappop, heappush
from math import inf, gcd, sqrt
from random import getrandbits
from types import GeneratorType
from typing import List
from collections import defaultdict
from bisect import bisect_left, bisect_right
from itertools import accumulate

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))
fmax = lambda x, y: x if x > y else y


def bootstrap(f, stack=None):
    if stack is None:
        stack = []

    def func(*args, **kwargs):
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

    return func


MOD = 10**9 + 7

mx = 2 * 10**5
# f = [0] * MX
# f[0] = f[1] = 1
# for i in range(2, MX):
#     f[i] = f[i - 1] + 2 * (i - 1) * f[i - 2]
#     f[i] %= MOD
# 阶乘
# fac = [1] * (mx + 1)
# for i in range(1, mx + 1):
#     fac[i] = fac[i - 1] * i % MOD
# # 逆元
# ifac = [0] * (mx + 1)
# ifac[mx] = pow(fac[mx], MOD - 2, MOD)
# for i in range(mx, 0, -1):
#     ifac[i - 1] = ifac[i] * i % MOD
#
#
# # 组合数
# def comb(n: int, m: int, MOD=MOD) -> int:
#     if m < 0 or m > n:
#         return 0
#     return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD


class BIT:
    def __init__(self, n: int):
        self.tree = [0] * n  # 树状数组
        self.n = n
        self.m = len(bin(n)[2:])

    def add(self, x: int, val: int) -> None:
        while x < self.n:
            self.tree[x] += val
            x |= x + 1

    # 维护权值和
    def sm(self, x: int) -> int:
        res = 0
        while x > 0:
            res += self.tree[x - 1]
            x &= x - 1
        return res

    def range_sm(self, l: int, r: int) -> int:
        return self.sm(r) - self.sm(l)

    def select(self, k: int):
        x = 0
        cur = 0
        i = 1 << self.m
        while i > 0:
            if x + i <= self.n and cur + self.tree[x + i - 1] <= k:
                x += i
                cur += self.tree[x - 1]
            i //= 2
        return x


# endregion fastio


# MOD = 998_244_353
# MOD = 10 ** 9 + 7
# DIR4 = ((-1, 0), (0, 1), (1, 0), (0, -1)) #URDL
# DIR8 = ((-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1))
def kmp(text: str, pattern: str) -> List[int]:
    m = len(pattern)
    pi = [0] * m
    c = 0
    for i in range(1, m):
        v = pattern[i]
        while c and pattern[c] != v:
            c = pi[c - 1]
        if pattern[c] == v:
            c += 1
        pi[i] = c

    res = []
    c = 0
    for i, v in enumerate(text):
        v = text[i]
        while c and pattern[c] != v:
            c = pi[c - 1]
        if pattern[c] == v:
            c += 1
        if c == len(pattern):
            res.append(i - m + 1)
            c = pi[c - 1]
    return res


def getLen(x: int) -> int:
    return len(bin(x)[2:])


def query(x) -> None:
    print("?", x, flush=True)


def answer(x) -> None:
    print("!", x, flush=True)


class Factorial:
    def __init__(self, N, mod) -> None:
        N += 1
        self.mod = mod
        self.f = [1 for _ in range(N)]
        self.g = [1 for _ in range(N)]
        for i in range(1, N):
            self.f[i] = self.f[i - 1] * i % self.mod
        self.g[-1] = pow(self.f[-1], mod - 2, mod)
        for i in range(N - 2, -1, -1):
            self.g[i] = self.g[i + 1] * (i + 1) % self.mod

    def fac(self, n):
        return self.f[n]

    def fac_inv(self, n):
        return self.g[n]

    def comb(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

    def perm(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[n - m] % self.mod

    def catalan(self, n):
        return (self.comb(2 * n, n) - self.comb(2 * n, n - 1)) % self.mod

    def inv(self, n):
        return self.f[n - 1] * self.g[n] % self.mod


def isPrime(x):
    for i in range(2, 10**18):
        if i * i > x:
            return True
        if x % i == 0:
            return False


dirs = [[-1, 0], [0, 1], [1, 0], [0, -1], [-1, -1], [-1, 1], [1, -1], [1, 1]]


def read_int():
    res = b""

    while True:
        d = sys.stdin.buffer.read(1)
        if d == b"-" or d.isdigit():
            res += d
        elif res:
            break

    return int(res)


# 标准并查集
class UnionFind:
    def __init__(self, n):
        self.root = [i for i in range(n)]
        self.size = [1] * n
        self.part = n
        self.mx_siz = 1

    def find(self, x):
        x = self.root[x]
        x_copy = x
        while x != self.root[x]:
            x = self.root[x]
        while x_copy != x:
            self.root[x_copy], x_copy = x, self.root[x_copy]
        return x

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        # if root_x < root_y:
        #     root_x, root_y = root_y, root_x
        self.root[root_x] = root_y
        self.size[root_y] += self.size[root_x]
        if self.size[root_y] > self.mx_siz:
            self.mx_siz = self.size[root_y]
        # 将非根节点的秩赋0
        self.size[root_x] = 0
        self.part -= 1
        return True

    def is_connected(self, x, y):
        return self.find(x) == self.find(y)

    def get_root_part(self):
        # 获取每个根节点对应的组
        part = defaultdict(list)
        n = len(self.root)
        for i in range(n):
            part[self.find(i)].append(i)
        return part

    def get_root_size(self):
        # 获取每个根节点对应的组大小
        size = defaultdict(int)
        n = len(self.root)
        for i in range(n):
            size[self.find(i)] = self.size[self.find(i)]
        return size


class LCA:
    def __init__(self, depth, parent):
        # g[v]: (cost, u)
        self.n = len(depth)
        self.num = self.n.bit_length()
        self.depth = depth
        self.parent = [[-1] * self.n for _ in range(self.num)]
        self.parent[0] = parent
        for k in range(self.num - 1):
            for v in range(self.n):
                if self.parent[k][v] == -1:
                    self.parent[k + 1][v] = -1
                else:
                    self.parent[k + 1][v] = self.parent[k][self.parent[k][v]]

    def getLCA(self, u, v):
        if self.depth[u] > self.depth[v]:
            u, v = v, u
        for k in range(self.num):
            if ((self.depth[v] - self.depth[u]) >> k) & 1:
                v = self.parent[k][v]
        if u == v:
            return u

        for k in reversed(range(self.num)):
            if self.parent[k][u] != self.parent[k][v]:
                u = self.parent[k][u]
                v = self.parent[k][v]
        return self.parent[0][u]

    def search(self, v, x):
        for k in reversed(range(self.num)):
            if x >> k & 1:
                v = self.parent[k][v]
        return v

    def getDis(self, u, v):
        return self.depth[u] + self.depth[v] - self.depth[self.getLCA(u, v)] * 2

    def addNode(self, cur, v):
        self.parent[0][cur] = v
        self.depth[cur] = self.depth[v] + 1
        for k in range(self.num - 1):
            if self.parent[k][cur] == -1:
                self.parent[k + 1][cur] = -1
            else:
                self.parent[k + 1][cur] = self.parent[k][self.parent[k][cur]]


mod = 10**9 + 7


def merge_count(a):
    n = len(a)
    if n <= 1:
        return 0
    left = a[: n // 2]
    right = a[n // 2 :]
    cnt = merge_count(left) + merge_count(right)
    l = r = 0
    merged = []
    while l < len(left) and r < len(right):
        if left[l] <= right[r]:
            merged.append(left[l])
            l += 1
        else:
            merged.append(right[r])
            cnt += len(left) - l
            r += 1
    merged.extend(left[l:])
    merged.extend(right[r:])
    a[:] = merged
    return cnt


class DSU:
    def __init__(self, n):
        self.f = list(range(n))
        self.siz = [1] * n

    def find(self, x):
        x = self.f[x]
        x_copy = x
        while x != self.f[x]:
            x = self.f[x]
        while x_copy != x:
            self.f[x_copy], x_copy = x, self.f[x_copy]
        return x

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        # if self.siz[x] < self.siz[y]:  # Union by size
        #     x, y = y, x
        self.siz[x] += self.siz[y]
        self.f[y] = x
        return True

    def size(self, x):
        return self.siz[self.find(x)]


def cf1363C():
    n, m, k = mint()

    x = [0] * (k + 1)
    y = [0] * (k + 1)
    for i in range(k + 1):
        x[i], y[i] = mint()
        x[i] -= 1
        y[i] -= 1

    dsu = DSU(n * m)
    loop = [0] * (n * m)
    e = [0] * (n * m)

    for i in range(k + 1):
        u = x[i] * m + y[i]
        loop[u] = 1
        e[u] += 1

    for i in range(1, k + 1):
        if abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]) != 2:
            print(0)
            return

        a, b, c, d = 0, 0, 0, 0
        if x[i] == x[i - 1]:
            a = x[i]
            b = (y[i] + y[i - 1]) // 2
            c = a
            d = b
        elif y[i] == y[i - 1]:
            a = (x[i] + x[i - 1]) // 2
            b = y[i]
            c = a
            d = b
        else:
            a = x[i]
            b = y[i - 1]
            c = x[i - 1]
            d = y[i]

        u = a * m + b
        v = c * m + d

        if not dsu.same(u, v):
            root_u = dsu.find(u)
            root_v = dsu.find(v)
            e[root_u] += e[root_v]
            loop[root_u] |= loop[root_v]
            dsu.merge(u, v)

        root = dsu.find(u)
        e[root] += 1
        if u == v:
            loop[root] = 1

    ans = 1
    MOD = 10**9 + 7

    for i in range(n * m):
        if dsu.find(i) == i:
            s = dsu.size(i)
            if e[i] > s:
                ans = 0
            elif e[i] == s:
                if not loop[i]:
                    ans = (ans * 2) % MOD
            else:
                ans = (ans * s) % MOD

    print(ans)
    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf1363C()
