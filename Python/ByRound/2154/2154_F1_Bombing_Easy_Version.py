# Problem: CF 2154 F1 - Bombing (Easy Version)
# https://codeforces.com/contest/2154/problem/F1

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^2)
Space Complexity: O(n)

This code solves the problem of counting the number of ways to fill -1 values in a permutation
such that the resulting permutation is a riffle shuffle of [1, 2, ..., n].

A riffle shuffle means the permutation can be split into two subsequences (left and right parts)
such that the original sequence [1, 2, ..., n] can be reconstructed by interleaving these two.

The approach uses dynamic programming:
1. For each possible split point k (number of elements in the first subsequence), 
   we calculate valid combinations.
2. We use combinatorics to count valid ways to choose positions for -1 elements.
3. The function `f(l, m)` computes valid arrangements for a given split point m.
4. We iterate over all possible split points (1 to n) and sum up all valid possibilities.
5. Special handling is done to adjust for edge cases where the permutation is already sorted.

The solution involves:
- Precomputation of factorials and their modular inverses for combination calculations
- Dynamic processing of the permutation to count valid combinations using combinatorics
- Modular arithmetic to handle large numbers
"""

import os
import random
import sys
from collections import defaultdict
from io import BytesIO, IOBase

BUFSIZE = 8192


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


sys.setrecursionlimit(10000)

mag = random.getrandbits(20)

lsum = lambda l, r: (l + r) * (r - l + 1) // 2


class D:
    def __init__(self, type=int):
        self.d = defaultdict(type)
        self.mag = random.getrandbits(20)

    def __setitem__(self, key, value):
        self.d[key + self.mag] = value

    def __getitem__(self, key):
        return self.d[key + self.mag]

    def __delitem__(self, key):
        del self.d[key + self.mag]

    def __contains__(self, key):
        return key + self.mag in self.d

    def __iter__(self):
        self.keys = iter(self.d.keys())
        return self

    def __next__(self):
        return next(self.keys) - self.mag

    def __len__(self):
        return len(self.d)

    def keys(self):
        r = []
        for k in self.d.keys():
            r.append(k - self.mag)
        return r


ii = lambda: int(input())
mii = lambda: map(int, input().split())
fii = lambda: map(float, input().split())
lmii = lambda: list(map(int, input().split()))
i2c = lambda n: chr(ord("a") + n)
c2i = lambda c: ord(c) - ord("a")

mod = 998244353


def gen_F(N):
    F = [1]
    for x in range(1, N + 1):
        F.append(F[-1] * x % mod)
    return F


def gen_rev(N):
    rev = [1, 1]
    for x in range(2, N + 1):
        y = mod // x + 1
        rev.append(y * rev[y * x % mod] % mod)
    return rev


def gen_F_(N):
    rev = gen_rev(N)
    F_ = [1, 1]
    for x in range(2, N + 1):
        F_.append(F_[-1] * rev[x] % mod)
    return F_


N = 3003
F = gen_F(N)
F_ = gen_F_(N)
Comb = lambda x, y: F[x] * F_[y] * F_[x - y] % mod


def f(l, m):
    n = len(l)

    r = 1
    blank = 0
    c0, c1 = 1, m + 1
    for i in range(n):
        if l[i] == -1:
            blank += 1
        else:
            if l[i] <= m:
                t = l[i] - c0
                # Check if position is valid
                if t < 0 or t > blank:
                    return 0
                # Multiply by number of ways to choose positions
                r = r * Comb(blank, t) % mod
                c0 = l[i] + 1
                c1 += blank - t
            else:
                t = l[i] - c1
                # Check if position is valid
                if t < 0 or t > blank:
                    return 0
                # Multiply by number of ways to choose positions
                r = r * Comb(blank, t) % mod
                c1 = l[i] + 1
                c0 += blank - t
            blank = 0
    # Final check for remaining elements
    t0, t1 = m + 1 - c0, n + 1 - c1
    if t0 < 0 or t0 > blank or t0 + t1 != blank:
        return 0
    r = r * Comb(blank, n + 1 - c1) % mod
    return r


ans = []
for _ in range(int(input())):
    n = ii()
    l = lmii()
    res = 0
    # For each possible split point m, calculate valid configurations
    for x in range(1, n + 1):
        res = (res + f(l, x)) % mod
    # Special edge case adjustment for sorted permutation
    if all(l[i] == i + 1 or l[i] == -1 for i in range(n)):
        res -= n - 1
    res = res % mod
    ans.append(res)

print("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/