# Contest 2084, Problem F: Skyscape
# URL: https://codeforces.com/contest/2084/problem/F


import sys, random, bisect
from collections import deque, defaultdict
from heapq import heapify, heappop, heappush
from itertools import permutations
from math import gcd, log

input = lambda: sys.stdin.buffer.readline()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


class SegmentTree:
    def __init__(self, init_val, segfunc, ide_ele):
        n = len(init_val)
        self.segfunc = segfunc
        self.ide_ele = ide_ele
        self.num = 1 << (n - 1).bit_length()
        self.tree = [ide_ele] * 2 * self.num
        self.size = n
        for i in range(n):
            self.tree[self.num + i] = init_val[i]
        for i in range(self.num - 1, 0, -1):
            self.tree[i] = self.segfunc(self.tree[2 * i], self.tree[2 * i + 1])

    def update(self, k, x):
        k += self.num
        self.tree[k] = x
        while k > 1:
            k >>= 1
            self.tree[k] = self.segfunc(self.tree[2 * k], self.tree[2 * k + 1])

    def query(self, l, r):
        if r == self.size:
            r = self.num

        res = self.ide_ele

        l += self.num
        r += self.num
        while l < r:
            if l & 1:
                res = self.segfunc(res, self.tree[l])
                l += 1
            if r & 1:
                res = self.segfunc(res, self.tree[r - 1])
            l >>= 1
            r >>= 1

        return res


def solve(N, A, B):
    for i in range(N):
        A[i] -= 1
        B[i] -= 1

    pos_on_B = [-1] * N
    for i in range(N):
        if B[i] != -1:
            pos_on_B[B[i]] = i

    seg0 = SegmentTree([-1] * N, max, -1)
    lmin = [-1] * N
    rmax = [-1] * N
    for i in range(N):
        if pos_on_B[A[i]] == -1:
            lmin[A[i]] = seg0.query(0, A[i]) + 1
            continue

        check = seg0.query(0, A[i])
        if check > pos_on_B[A[i]]:
            return (False, [])
        seg0.update(A[i], pos_on_B[A[i]])

    seg1 = SegmentTree([N] * N, min, N)
    for i in range(N)[::-1]:
        if pos_on_B[A[i]] == -1:
            rmax[A[i]] = seg1.query(A[i] + 1, N) - 1
        else:
            seg1.update(A[i], pos_on_B[A[i]])

    l_to_rv = [[] for l in range(N)]
    for i in range(N):
        if pos_on_B[A[i]] != -1:
            continue
        if lmin[A[i]] == N:
            return (False, [])
        l_to_rv[lmin[A[i]]].append((rmax[A[i]], A[i]))

    # print(l_to_rv)
    pq = []
    res = B[:]
    for i in range(N):
        for r, val in l_to_rv[i]:
            heappush(pq, r * N + val)
        if B[i] != -1:
            continue
        if not pq:
            return (False, [])
        rv = heappop(pq)
        r, val = rv // N, rv % N
        if r < i:
            return (False, [])
        res[i] = val

    return (True, [x + 1 for x in res])


for _ in range(int(input())):
    N = int(input())
    A = li()
    B = li()
    flg, res = solve(N, A, B)

    if not flg:
        print(-1)
    else:
        print(*res)
