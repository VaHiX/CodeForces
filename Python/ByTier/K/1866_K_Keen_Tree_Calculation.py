# Contest 1866, Problem K: Keen Tree Calculation
# URL: https://codeforces.com/contest/1866/problem/K

# Visit my repo: https://github.com/Yawn-Sean/Daily_CF_Problems
standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import io, os, sys

        input = lambda: sys.stdin.readline().strip()

        import math

        inf = math.inf

        def I():
            return input()

        def II():
            return int(input())

        def MII():
            return map(int, input().split())

        def LI():
            return input().split()

        def LII():
            return list(map(int, input().split()))

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        from io import BytesIO, IOBase

        import random
        import os

        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, lru_cache, reduce
        from heapq import (
            merge,
            heapify,
            heappop,
            heappush,
            heappushpop,
            nlargest,
            nsmallest,
        )
        from itertools import accumulate, combinations, permutations, count, product
        from operator import add, iand, ior, itemgetter, mul, xor
        from string import ascii_lowercase, ascii_uppercase, ascii_letters
        from typing import *

        BUFSIZE = 4096

    if output_together:

        class FastIO(IOBase):
            newlines = 0

            def __init__(self, file):
                self._fd = file.fileno()
                self.buffer = BytesIO()
                self.writable = "x" in file.mode or "r" not in file.mode
                self.write = self.buffer.write if self.writable else None

            def read(self):
                while True:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    if not b:
                        break
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines = 0
                return self.buffer.read()

            def readline(self):
                while self.newlines == 0:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    self.newlines = b.count(b"\n") + (not b)
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines -= 1
                return self.buffer.readline()

            def flush(self):
                if self.writable:
                    os.write(self._fd, self.buffer.getvalue())
                    self.buffer.truncate(0), self.buffer.seek(0)

        class IOWrapper(IOBase):
            def __init__(self, file):
                self.buffer = FastIO(file)
                self.flush = self.buffer.flush
                self.writable = self.buffer.writable
                self.write = lambda s: self.buffer.write(s.encode("ascii"))
                self.read = lambda: self.buffer.read().decode("ascii")
                self.readline = lambda: self.buffer.readline().decode("ascii")

        sys.stdout = IOWrapper(sys.stdout)

    if dfs:
        from types import GeneratorType

        def bootstrap(f, stk=[]):
            def wrappedfunc(*args, **kwargs):
                if stk:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stk.append(to)
                            to = next(to)
                        else:
                            stk.pop()
                            if not stk:
                                break
                            to = stk[-1].send(to)
                    return to

            return wrappedfunc

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.notest = [-1] * (n + 1)

        def append(self, i, j):
            self.pre.append(self.notest[i])
            self.notest[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.notest[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]


n = II()
path = [[] for _ in range(n)]

for _ in range(n - 1):
    u, v, w = MII()
    u -= 1
    v -= 1
    path[u].append(w * n + v)
    path[v].append(w * n + u)

que = [0]
parent = [-1] * n
parent_weight = [0] * n

for u in que:
    for msk in path[u]:
        w, v = divmod(msk, n)
        if parent[u] != v:
            parent[v] = u
            parent_weight[v] = w
            que.append(v)

dp = [0] * n
for i in range(n - 1, 0, -1):
    u = que[i]
    p = parent[u]
    dp[p] = fmax(dp[p], dp[u] + parent_weight[u])

dp1 = [0] * n
for i in range(n):
    u = que[i]

    ma1, ma2 = dp1[u], 0

    for msk in path[u]:
        v = msk % n
        if parent[v] == u:
            d = dp[v] + parent_weight[v]
            if d >= ma1:
                ma1, ma2 = d, ma1
            elif d >= ma2:
                ma2 = d

    for msk in path[u]:
        w, v = divmod(msk, n)
        if parent[v] == u:
            d = dp[v] + parent_weight[v]
            if d == ma1:
                dp1[v] = ma2 + w
            else:
                dp1[v] = ma1 + w

d0 = fmax(max(dp), max(dp1))

k1 = [[] for _ in range(n)]
b1 = [[] for _ in range(n)]
k2 = [[] for _ in range(n)]
b2 = [[] for _ in range(n)]

for u in range(n):
    ks = []
    bs = []

    for msk in path[u]:
        w, v = divmod(msk, n)

        if v == parent[u]:
            ks.append(w)
            bs.append(dp1[u] - w)
        else:
            ks.append(w)
            bs.append(dp[v])

    l = len(ks)
    st_range = sorted(range(l), key=lambda x: -bs[x])
    st_range.sort(key=lambda x: ks[x])

    used = [0] * l

    ch = []
    for i in range(l):
        k = ks[st_range[i]]
        b = bs[st_range[i]]

        if ch and ks[st_range[ch[-1]]] == k:
            continue

        while len(ch) > 1:
            vk1 = ks[st_range[ch[-2]]]
            vb1 = bs[st_range[ch[-2]]]
            vk2 = ks[st_range[ch[-1]]]
            vb2 = bs[st_range[ch[-1]]]

            if (vb2 - vb1) * (vk2 - k) >= (b - vb2) * (vk1 - vk2):
                ch.pop()
            else:
                break

        ch.append(i)

    for i in ch:
        used[i] = 1
        i = st_range[i]
        k1[u].append(ks[i])
        b1[u].append(bs[i])

    ch = []
    for i in range(l):
        if used[i]:
            continue

        k = ks[st_range[i]]
        b = bs[st_range[i]]

        if ch and ks[st_range[ch[-1]]] == k:
            continue

        while len(ch) > 1:
            vk1 = ks[st_range[ch[-2]]]
            vb1 = bs[st_range[ch[-2]]]
            vk2 = ks[st_range[ch[-1]]]
            vb2 = bs[st_range[ch[-1]]]

            if (vb2 - vb1) * (vk2 - k) >= (b - vb2) * (vk1 - vk2):
                ch.pop()
            else:
                break

        ch.append(i)

    for i in ch:
        i = st_range[i]
        k2[u].append(ks[i])
        b2[u].append(bs[i])

q = II()
outs = []

for _ in range(q):
    x, k = MII()
    x -= 1

    l, r = 0, len(k1[x]) - 2

    while l <= r:
        m = (l + r) // 2
        if k1[x][m] * k + b1[x][m] >= k1[x][m + 1] * k + b1[x][m + 1]:
            r = m - 1
        else:
            l = m + 1

    v1, v2 = 0, 0
    for i in range(l - 1, l + 2):
        if 0 <= i < len(k1[x]):
            res = k1[x][i] * k + b1[x][i]
            if res > v1:
                v1, v2 = res, v1
            elif res > v2:
                v2 = res

    if len(k2[x]):
        l, r = 0, len(k2[x]) - 2
        while l <= r:
            m = (l + r) // 2
            if k2[x][m] * k + b2[x][m] >= k2[x][m + 1] * k + b2[x][m + 1]:
                r = m - 1
            else:
                l = m + 1

        for i in range(l - 1, l + 2):
            if 0 <= i < len(k2[x]):
                res = k2[x][i] * k + b2[x][i]
                if res > v1:
                    v1, v2 = res, v1
                elif res > v2:
                    v2 = res

    outs.append(fmax(v1 + v2, d0))

print("\n".join(map(str, outs)))
