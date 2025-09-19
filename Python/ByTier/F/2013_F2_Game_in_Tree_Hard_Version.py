# Contest 2013, Problem F2: Game in Tree (Hard Version)
# URL: https://codeforces.com/contest/2013/problem/F2

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
            return list(input().split())

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
        from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest
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
        file = open("input.txt", "r", encoding='utf-16').readline().strip()[1:-1]
        fin = open(file, 'r')
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")
        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:
        def debug(*args, **kwargs):
            print('\033[92m', end='')
            print(*args, **kwargs)
            print('\033[0m', end='')

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.lst = [-1] * n
        
        def append(self, i, j):
            self.pre.append(self.lst[i])
            self.lst[i] = len(self.cur)
            self.cur.append(j)
        
        def iterate(self, i):
            tmp = self.lst[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]

class SparseTable:
    def __init__(self, data, merge_method):
        self.note = [0] * (len(data) + 1)
        self.merge_method = merge_method
        l, r, v = 1, 2, 0
        while True:
            for i in range(l, r):
                if i >= len(self.note):
                    break
                self.note[i] = v
            else:
                l *= 2
                r *= 2
                v += 1
                continue
            break
        self.ST = [[0] * len(data) for _ in range(self.note[-1]+1)]
        self.ST[0] = data
        for i in range(1, len(self.ST)):
            for j in range(len(data) - (1 << i) + 1):
                self.ST[i][j] = merge_method(self.ST[i-1][j], self.ST[i-1][j + (1 << (i-1))])

    def query(self, l, r):
        if l > r: return -10 ** 7
        pos = self.note[r-l+1]
        return self.merge_method(self.ST[pos][l], self.ST[pos][r - (1 << pos) + 1])

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
    
    def init(self):
        for i in range(len(self.parent)):
            self.parent[i] = i

    def find(self, a):
        a = self.parent[a]
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def merge(self, a, b):
        pa, pb = self.find(a), self.find(b)
        if pa == pb: return False
        self.parent[pb] = pa
        return True

def solve(p):
    to_root = [p]
    while to_root[-1]:
        to_root.append(parent[to_root[-1]])
    
    to_root.reverse()
    
    on_path = [0] * n
    dis = [0] * n
    
    for x in to_root:
        on_path[x] = 1
    
    for i in order:
        if not on_path[i]:
            dis[parent[i]] = fmax(dis[parent[i]], dis[i] + 1)

    ar = [dis[x] for x in to_root]
    k = len(ar)

    ar1 = [ar[i] + i for i in range(k)]
    ar2 = [ar[i] - i for i in range(k)]
    
    st1 = SparseTable(ar1, fmax)
    st2 = SparseTable(ar2, fmax)
    union = UnionFind(k + 1)
    
    fa = [2 * k] * (k + 1)

    for i in range(1, k):
        l, r = i + 1, k - 1
        while l <= r:
            m = (l + r) // 2
            if st2.query(i + 1, m) + m < ar1[i] - i:
                l = m + 1
            else:
                r = m - 1
        if i < r:
            left = fmin(2 * i, k)
            right = fmin(r + i, k - 1)
            while True:
                left = union.find(left)
                if left > right: break
                fa[left] = i
                union.merge(left + 1, left)
    
    union.init()
    
    fb = [-2 * k] * (k + 1)
    
    for i in range(k - 1, 0, -1):
        l, r = 1, i - 1
        while l <= r:
            m = (l + r) // 2
            if st1.query(m, i - 1) - m + 1 <= ar2[i] + i:
                r = m - 1
            else:
                l = m + 1
        if r >= 0:
            left = fmin(r + i, k)
            right = fmin(2 * i - 1, k - 1)
            while True:
                left = union.find(left)
                if left > right: break
                fb[left] = i
                union.merge(left + 1, left)
    
    ar2.append(-1)
    for i in range(k - 1, 0, -1):
        ar2[i] = fmax(ar2[i + 1] + 1, ar[i])
        if ar2[i] >= st1.query(1, i - 1):
            fb[i] = i
        if ar1[0] > fmax(st2.query(1, i - 1) + i, ar2[i]):
            fa[i] = 0
        if fa[i] <= i - fb[i]:
            flg[to_root[i]] = 1

t = II()
outs = []

for _ in range(t):
    n = II()
    path = [[] for _ in range(n)]
    
    for _ in range(n - 1):
        u, v = GMI()
        path[u].append(v)
        path[v].append(u)
    
    parent = [-1] * n
    order = []
    
    stk = [0]
    while stk:
        u = stk.pop()
        order.append(u)
        for v in path[u]:
            if parent[u] != v:
                parent[v] = u
                stk.append(v)
    
    order.reverse()
    
    flg = [0] * n
    
    p1, p2 = GMI()
    
    solve(p1)
    solve(p2)
    
    for i in range(n):
        parent[i] = -1
    
    stk = [p2]
    while stk:
        u = stk.pop()
        order.append(u)
        for v in path[u]:
            if parent[u] != v:
                parent[v] = u
                stk.append(v)
    
    cur = p1
    
    while cur != -1:
        outs.append('Alice' if flg[cur] else 'Bob')
        cur = parent[cur]

print('\n'.join(outs))