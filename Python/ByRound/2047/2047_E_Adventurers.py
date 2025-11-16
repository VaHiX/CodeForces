# Problem: CF 2047 E - Adventurers
# https://codeforces.com/contest/2047/problem/E

"""
Algorithm: Binary search on the answer + Segment Tree for range queries
Time Complexity: O(N * log(N) * log(max_coord))
Space Complexity: O(N)

The problem involves distributing cities among four merchants such that the minimum number of cities any merchant gets is maximized. 
We perform binary search on the number of cities (k) that each merchant can get. For each k, we check if there exists a dividing point
(x0, y0) such that each merchant gets at least k cities. To do this efficiently, we use a segment tree to quickly calculate how many cities
fall into each quadrant.

Approach:
1. Binary search on the number of cities each merchant can get (from 0 to N//4)
2. For a given k, we check if there's a valid (x0, y0) point satisfying the constraint
3. Use preprocessing to map coordinates to indices
4. Use segment trees to maintain counts in each quadrant efficiently during traversal
"""

from random import randrange

H = randrange(1, 1 << 60)


def Hash(n):
    return n ^ H


def compress(A):
    S = sorted(A)
    nS = []
    for s in S:
        if not nS or nS[-1] != s:
            nS.append(s)
    S = nS[:]
    D = dict()
    DR = dict()
    for i in range(len(S)):
        D[Hash(S[i])] = i
        DR[Hash(i)] = S[i]
    return D, DR


def op(x, y):
    return x + y


class SegTree:
    def __init__(self, init_val, op, ide_ele):
        n = len(init_val)
        self.n = n
        self.op = op
        self.ide_ele = ide_ele
        self.num = 1 << (n - 1).bit_length()
        self.tree = [ide_ele] * 2 * self.num
        for i in range(n):
            self.tree[self.num + i] = init_val[i]
        for i in range(self.num - 1, 0, -1):
            self.tree[i] = self.op(self.tree[2 * i], self.tree[2 * i + 1])

    def update(self, k, x):
        k += self.num
        self.tree[k] = x
        while k > 1:
            self.tree[k >> 1] = self.op(self.tree[k], self.tree[k ^ 1])
            k >>= 1

    def query(self, l, r):
        res = self.ide_ele

        l += self.num
        r += self.num
        while l < r:
            if l & 1:
                res = self.op(res, self.tree[l])
                l += 1
            if r & 1:
                res = self.op(res, self.tree[r - 1])
            l >>= 1
            r >>= 1
        return res

    def __getitem__(self, n):
        return self.tree[self.num + n]

    def List(self):
        return self.tree[self.num : self.num + self.n]

    def max_right(self, l, f, limit):
        if l == self.n:
            return self.n
        l += self.num
        sm = self.ide_ele
        while True:
            while l % 2 == 0:
                l >>= 1
            if not f(self.op(sm, self.tree[l]), limit):
                while l < self.num:
                    l <<= 1
                    if f(self.op(sm, self.tree[l]), limit):
                        sm = self.op(sm, self.tree[l])
                        l += 1
                return l - self.num
            sm = self.op(sm, self.tree[l])
            l += 1
            if l & -l == l:
                break
        return self.n

    def min_left(self, r, f, limit):
        if r == 0:
            return 0
        r += self.num
        sm = self.ide_ele
        while True:
            r -= 1
            while r > 1 and r % 2 == 1:
                r >>= 1
            if not f(self.op(self.tree[r], sm), limit):
                while r < self.num:
                    r = 2 * r + 1
                    if f(self.op(self.tree[r], sm), limit):
                        sm = self.op(self.tree[r], sm)
                        r -= 1
                return r + 1 - self.num
            sm = self.op(self.tree[r], sm)
            if r & -r == r:
                break
        return 0


def bisect_R(n, limit):
    return n < limit


for _ in range(int(input())):
    N = int(input())
    XY = sorted([list(map(int, input().split())) for _ in range(N)], key=lambda x: x[0])

    idxX, idxXR = compress([x for x, y in XY])
    idxY, idxYR = compress([y for x, y in XY])
    xy = [[] for _ in range(len(idxX))]
    for x, y in XY:
        xy[idxX[Hash(x)]].append(idxY[Hash(y)])
    B = []
    for x, y in XY:
        B.append((idxX[Hash(x)], idxY[Hash(y)]))

    left = 0
    right = N // 4 + 1
    ansX, ansY = 0, 0
    while left + 1 < right:
        mid = (left + right) // 2
        segL = SegTree([0] * len(idxY), op, 0)
        segR = SegTree([0] * len(idxY), op, 0)
        for x, y in B:
            segR.update(y, segR[y] + 1)
        sumL, sumR = 0, N
        for i, X in enumerate(xy):
            for y in X:
                segR.update(y, segR[y] - 1)
                segL.update(y, segL[y] + 1)
                sumR -= 1
                sumL += 1
            if min(sumL, sumR) < mid * 2:
                continue
            l1, r1 = segL.max_right(0, bisect_R, mid) + 1, segL.max_right(
                0, bisect_R, sumL - mid + 1
            )
            l2, r2 = segR.max_right(0, bisect_R, mid) + 1, segR.max_right(
                0, bisect_R, sumR - mid + 1
            )
            if max(l1, l2) <= min(r1, r2):
                left = mid
                ansX, ansY = idxXR[Hash(i)] + 1, idxYR[Hash(max(l1, l2))]
                break
        else:
            right = mid

    print(left)
    print(ansX, ansY)


# https://github.com/VaHiX/CodeForces/