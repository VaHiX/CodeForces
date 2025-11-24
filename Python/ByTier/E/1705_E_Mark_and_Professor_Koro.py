# Problem: CF 1705 E - Mark and Professor Koro
# https://codeforces.com/contest/1705/problem/E

"""
Algorithm: Segment Tree with Lazy Propagation
Purpose: Efficiently maintain and update frequency counts of integers in a range, supporting operations to add/subtract elements and compute maximum achievable value via merging operations.

Time Complexity: 
  - Initialization: O(n) where n is the size of the input array
  - Each update (add/sub): O(log n) 
  - Answer query: O(log n)
  - Overall: O(q * log n) for q queries

Space Complexity: O(n) for the segment tree and auxiliary arrays

Techniques:
- Lazy Segment Tree for efficient range updates
- Bit manipulation for encoding frequency states (0, 1, 2, 3)
- Custom operations for segment tree nodes
"""

class lazy_segtree:
    def update(self, k):
        self.d[k] = self.op(self.d[2 * k], self.d[2 * k + 1])

    def all_apply(self, k, f):
        self.d[k] = self.mapping(f, self.d[k])
        if k < self.size:
            self.lz[k] = self.composition(f, self.lz[k])

    def push(self, k):
        self.all_apply(2 * k, self.lz[k])
        self.all_apply(2 * k + 1, self.lz[k])
        self.lz[k] = self.identity

    def __init__(self, V, OP, E, MAPPING, COMPOSITION, ID):
        self.n = len(V)
        self.log = (self.n - 1).bit_length()
        self.size = 1 << self.log
        self.d = [E for i in range(2 * self.size)]
        self.lz = [ID for i in range(self.size)]
        self.e = E
        self.op = OP
        self.mapping = MAPPING
        self.composition = COMPOSITION
        self.identity = ID
        for i in range(self.n):
            self.d[self.size + i] = V[i]
        for i in range(self.size - 1, 0, -1):
            self.update(i)

    def set(self, p, x):
        assert 0 <= p and p < self.n
        p += self.size
        for i in range(self.log, 0, -1):
            self.push(p >> i)
        self.d[p] = x
        for i in range(1, self.log + 1):
            self.update(p >> i)

    def get(self, p):
        assert 0 <= p and p < self.n
        p += self.size
        for i in range(self.log, 0, -1):
            self.push(p >> i)
        return self.d[p]

    def prod(self, l, r):
        assert 0 <= l and l <= r and r <= self.n
        if l == r:
            return self.e
        l += self.size
        r += self.size
        for i in range(self.log, 0, -1):
            if ((l >> i) << i) != l:
                self.push(l >> i)
            if ((r >> i) << i) != r:
                self.push(r >> i)
        sml, smr = self.e, self.e
        while l < r:
            if l & 1:
                sml = self.op(sml, self.d[l])
                l += 1
            if r & 1:
                r -= 1
                smr = self.op(self.d[r], smr)
            l >>= 1
            r >>= 1
        return self.op(sml, smr)

    def all_prod(self):
        return self.d[1]

    def apply_point(self, p, f):
        assert 0 <= p and p < self.n
        p += self.size
        for i in range(self.log, 0, -1):
            self.push(p >> i)
        self.d[p] = self.mapping(f, self.d[p])
        for i in range(1, self.log + 1):
            self.update(p >> i)

    def apply(self, l, r, f):
        assert 0 <= l and l <= r and r <= self.n
        if l == r:
            return
        l += self.size
        r += self.size
        for i in range(self.log, 0, -1):
            if ((l >> i) << i) != l:
                self.push(l >> i)
            if ((r >> i) << i) != r:
                self.push((r - 1) >> i)
        l2, r2 = l, r
        while l < r:
            if l & 1:
                self.all_apply(l, f)
                l += 1
            if r & 1:
                r -= 1
                self.all_apply(r, f)
            l >>= 1
            r >>= 1
        l, r = l2, r2
        for i in range(1, self.log + 1):
            if ((l >> i) << i) != l:
                self.update(l >> i)
            if ((r >> i) << i) != r:
                self.update((r - 1) >> i)

    def max_right(self, l, g):
        assert 0 <= l and l <= self.n
        assert g(self.e)
        if l == self.n:
            return self.n
        l += self.size
        for i in range(self.log, 0, -1):
            self.push(l >> i)
        sm = self.e
        while 1:
            while l % 2 == 0:
                l >>= 1
            if not (g(self.op(sm, self.d[l]))):
                while l < self.size:
                    self.push(l)
                    l = 2 * l
                    if g(self.op(sm, self.d[l])):
                        sm = self.op(sm, self.d[l])
                        l += 1
                return l - self.size
            sm = self.op(sm, self.d[l])
            l += 1
            if (l & -l) == l:
                break
        return self.n

    def min_left(self, r, g):
        assert 0 <= r and r <= self.n
        assert g(self.e)
        if r == 0:
            return 0
        r += self.size
        for i in range(self.log, 0, -1):
            self.push((r - 1) >> i)
        sm = self.e
        while 1:
            r -= 1
            while r > 1 and (r % 2):
                r >>= 1
            if not (g(self.op(self.d[r], sm))):
                while r < self.size:
                    self.push(r)
                    r = 2 * r + 1
                    if g(self.op(self.d[r], sm)):
                        sm = self.op(self.d[r], sm)
                        r -= 1
                return r + 1 - self.size
            sm = self.op(self.d[r], sm)
            if (r & -r) == r:
                break
        return 0


from sys import stdin

input = lambda: stdin.readline()[:-1]

m = 2 * 10**5 + 100


def op1(x, y):
    return min(x, y)


def op2(x, y):
    return max(x, y)


def op(x, y):
    return ((x & y) & 1) + ((x | y) & 2)


def mapping(f, x):
    if f == id:
        return x
    else:
        return f


def comp(f, g):
    if f == id:
        return g
    return f


id = 1 << 20


def add(x):
    if seg.get(x) == 0:
        seg.apply(x, x + 1, 3)
        return

    def f(y):
        return y & 1 == 1

    r = seg.max_right(x, f)
    seg.apply(x, r, 0)
    seg.apply(r, r + 1, 3)
    return


def sub(x):
    if seg.get(x) == 3:
        seg.apply(x, x + 1, 0)
        return

    def f(y):
        return y & 2 == 0

    r = seg.max_right(x, f)
    seg.apply(x, r, 3)
    seg.apply(r, r + 1, 0)


def ans(x):
    def f(y):
        return y & 2 == 0

    l = seg.min_left(m, f)
    ANS[x] = l - 1


n, q = map(int, input().split())
a = list(map(int, input().split()))
c = [0] * m
for i in a:
    c[i] += 1

res = 0
for i in range(m):
    res //= 2
    res += c[i]
    c[i] = (res % 2) * 3

seg = lazy_segtree(c, op, 1, mapping, comp, id)
ANS = [0] * q
for i in range(q):
    x, y = map(int, input().split())
    x -= 1
    sub(a[x])
    a[x] = y
    add(a[x])
    ans(i)
print(*ANS, sep="\n")


# https://github.com/VaHiX/CodeForces/