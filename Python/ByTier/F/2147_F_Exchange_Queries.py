# Problem: CF 2147 F - Exchange Queries
# https://codeforces.com/contest/2147/problem/F

"""
F. Exchange Queries
Algorithm: Segment Tree with Lazy Propagation
Time Complexity: O((n + q) * log n) per test case
Space Complexity: O(n)

This problem involves two traders with permutations p and s representing 
the relative values of items for each trader. An item i is at least as valuable as 
item j if we can trade from i to j using the traders' rules.

We use a segment tree to maintain information about reachability:
- Each node stores minimum value in range (mn)
- Leftmost and rightmost indices of min value (lm, rm)  
- Squared sum of distances between leftmost and rightmost indices (sq)
- Lazy propagation for efficient updates

The key insight is that if we can reach all items from any item, then the answer 
is n^2 + sum of squared distances / 2. 
"""

import sys


class ST:
    __slots__ = ("n", "mn", "lm", "rm", "sq", "lz")

    def __init__(self, n):
        self.n = n
        sz = 4 * (n + 5)
        self.mn = [0] * sz
        self.lm = [0] * sz
        self.rm = [0] * sz
        self.sq = [0] * sz
        self.lz = [0] * sz
        self.b(1, 1, n)

    def b(self, i, l, r):
        if l == r:
            self.mn[i] = 0
            self.lm[i] = l
            self.rm[i] = l
            self.sq[i] = 0
            return
        m = (l + r) >> 1
        li = i << 1
        ri = li | 1
        self.b(li, l, m)
        self.b(ri, m + 1, r)
        self.u(i, li, ri)

    def ap(self, i, d):
        self.mn[i] += d
        self.lz[i] += d

    def ps(self, i):
        d = self.lz[i]
        if d:
            li = i << 1
            ri = li | 1
            self.ap(li, d)
            self.ap(ri, d)
            self.lz[i] = 0

    def u(self, i, li, ri):
        ml = self.mn[li]
        mr = self.mn[ri]
        if ml < mr:
            self.mn[i] = ml
            self.lm[i] = self.lm[li]
            self.rm[i] = self.rm[li]
            self.sq[i] = self.sq[li]
        elif mr < ml:
            self.mn[i] = mr
            self.lm[i] = self.lm[ri]
            self.rm[i] = self.rm[ri]
            self.sq[i] = self.sq[ri]
        else:
            self.mn[i] = ml
            self.lm[i] = self.lm[li]
            self.rm[i] = self.rm[ri]
            g = self.lm[ri] - self.rm[li]
            self.sq[i] = self.sq[li] + self.sq[ri] + g * g

    def ad(self, ql, qr, d, i=1, l=1, r=None):
        if r is None:
            r = self.n
        if ql > r or qr < l:
            return
        if ql <= l and r <= qr:
            self.ap(i, d)
            return
        self.ps(i)
        m = (l + r) >> 1
        li = i << 1
        ri = li | 1
        if ql <= m:
            self.ad(ql, qr, d, li, l, m)
        if qr > m:
            self.ad(ql, qr, d, ri, m + 1, r)
        self.u(i, li, ri)

    def f(self):
        return self.lm[1]

    def g(self):
        return self.sq[1]


def solve():
    it = iter(sys.stdin.buffer.read().split())
    t = int(next(it))
    o = []
    for _ in range(t):
        n = int(next(it))
        q = int(next(it))
        p = [0] * (n + 1)
        s = [0] * (n + 1)
        for i in range(1, n + 1):
            p[i] = int(next(it))
        for i in range(1, n + 1):
            s[i] = int(next(it))
        A = [0] * (n + 1)
        pos = [0] * (n + 1)
        for i in range(1, n + 1):
            A[s[i]] = p[i]
        for r in range(1, n + 1):
            pos[A[r]] = r
        st = ST(n)
        for v in range(1, n + 1):
            r = pos[v]
            if v <= r - 1:
                st.ad(v, r - 1, 1)

        def mv(v, ro, rn):
            if v <= ro - 1:
                st.ad(v, ro - 1, -1)
            if v <= rn - 1:
                st.ad(v, rn - 1, 1)
            pos[v] = rn

        def sw(r1, r2):
            if r1 == r2:
                return
            v1 = A[r1]
            v2 = A[r2]
            if v1 == v2:
                return
            mv(v1, r1, r2)
            mv(v2, r2, r1)
            A[r1], A[r2] = v2, v1

        def ans():
            S = st.f() ** 2 + st.g()
            return (n * n + S) // 2

        for _q in range(q):
            tp = int(next(it))
            i = int(next(it))
            j = int(next(it))
            r1, r2 = s[i], s[j]
            sw(r1, r2)
            if tp == 1:
                p[i], p[j] = p[j], p[i]
            else:
                s[i], s[j] = s[j], s[i]
            o.append(str(ans()))
    sys.stdout.write("\n".join(o))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/