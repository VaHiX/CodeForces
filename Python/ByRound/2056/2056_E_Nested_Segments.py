# Contest 2056, Problem E: Nested Segments
# URL: https://codeforces.com/contest/2056/problem/E

from sys import stdin

input = lambda: stdin.readline()[:-1]


class segtree:
    def __init__(self, init, func, ide):
        self.n = len(init)
        self.func = func
        self.ide = ide
        self.size = 1 << (self.n - 1).bit_length()
        self.tree = [self.ide for i in range(2 * self.size)]
        for i in range(self.n):
            self.tree[self.size + i] = init[i]
        for i in range(self.size - 1, 0, -1):
            self.tree[i] = self.func(self.tree[2 * i], self.tree[2 * i | 1])

    def update(self, k, x):
        k += self.size
        self.tree[k] = x
        k >>= 1
        while k:
            self.tree[k] = self.func(self.tree[2 * k], self.tree[k * 2 | 1])
            k >>= 1

    def get(self, i):
        return self.tree[i + self.size]

    def query(self, l, r):
        l += self.size
        r += self.size
        l_res = self.ide
        r_res = self.ide
        while l < r:
            if l & 1:
                l_res = self.func(l_res, self.tree[l])
                l += 1
            if r & 1:
                r -= 1
                r_res = self.func(self.tree[r], r_res)
            l >>= 1
            r >>= 1
        return self.func(l_res, r_res)

    def max_right(self, l, f):
        assert 0 <= l <= self.n
        assert f(self.ide)
        if l == self.n:
            return self.n
        l += self.size
        res = self.ide
        while True:
            while l & 1 == 0:
                l >>= 1
            if not f(self.func(res, self.tree[l])):
                while l < self.size:
                    l *= 2
                    if f(self.func(res, self.tree[l])):
                        res = self.func(res, self.tree[l])
                        l += 1
                return l - self.size
            res = self.func(res, self.tree[l])
            l += 1
            if l & (-l) == l:
                break
        return self.n

    def min_left(self, r, f):
        assert 0 <= r <= self.n
        assert f(self.ide)
        if r == 0:
            return 0
        r += self.size
        res = self.ide
        while True:
            r -= 1
            while r > 1 and r & 1:
                r >>= 1
            if not f(self.func(self.tree[r], res)):
                while r < self.size:
                    r = 2 * r + 1
                    if f(self.func(self.tree[r], res)):
                        res = self.func(self.tree[r], res)
                        r -= 1
                return r + 1 - self.size
            res = self.func(self.tree[r], res)
            if r & (-r) == r:
                break
        return 0

    def __getitem__(self, i):
        return self.get(i)

    def __setitem__(self, key, val):
        self.update(key, val)

    def __iter__(self):
        for i in range(self.n):
            yield self.tree[i + self.size]

    def __str__(self):
        return str(list(self))


mod = 998244353
table_size = 4 * 10**5

fac = [1] * (table_size + 1)
finv = [1] * (table_size + 1)

for i in range(2, table_size + 1):
    fac[i] = fac[i - 1] * i % mod
finv[table_size] = pow(fac[table_size], mod - 2, mod)
for i in range(table_size - 1, -1, -1):
    finv[i] = finv[i + 1] * (i + 1) % mod


def rebuild(n):
    global table_size, fac, finv
    fac += [0] * (n - table_size)
    fac += [0] * (n - table_size)
    finv += [0] * (n - table_size)
    for i in range(table_size + 1, n + 1):
        fac[i] = fac[i - 1] * i % mod
    finv[n] = inv(fac[n])
    for i in range(n - 1, table_size, -1):
        finv[i] = finv[i + 1] * (i + 1) % mod
    table_size = n


def binom(n, k):
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    if n > table_size:
        rebuild(n + 10**4)
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def fpow(x, k):
    res = 1
    while k:
        if k & 1:
            res = res * x % mod
        x = x * x % mod
        k >>= 1
    return res


def inv(a):
    if a < table_size:
        return fac[a - 1] * finv[a] % mod
    return fpow(a, mod - 2)


def Cat(n):
    return binom(2 * n, n) * inv(n + 1) % mod


def solve():
    n, q = map(int, input().split())
    res = [(1 << 30, 0, n - 1)]
    for _ in range(q):
        l, r = map(lambda x: int(x) - 1, input().split())
        if l == r:
            continue
        res.append((r - l, l, r))
    res.sort(key=lambda x: x[0])
    seg = segtree(list(range(n)), max, -1)
    ans = 1
    for _, l, r in res:
        c = 0
        while True:
            mx = seg.query(l, r)
            if mx == -1:
                break
            c += 1
            seg[mx] = -1
        # seg[l]=l
        ans *= Cat(c)
        ans %= mod
    print(ans % mod)


for _ in range(int(input())):
    solve()
