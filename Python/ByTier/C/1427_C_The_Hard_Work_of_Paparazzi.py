# Contest 1427, Problem C: The Hard Work of Paparazzi
# URL: https://codeforces.com/contest/1427/problem/C


from heapq import heapify, heappop, heappush
from itertools import cycle
from math import sqrt, ceil
import os

import sys
from collections import defaultdict, deque
from io import BytesIO, IOBase
import sys
from array import array
from math import gcd
from random import randint

# input = lambda: sys.stdin.readline().rstrip("\r\n")
# inp = lambda dtype: [dtype(x) for x in input().split()]
# debug = lambda *x: print(*x, file=sys.stderr)
# ceil1 = lambda a, b: (a + b - 1) // b
# out, tests = [], 1
# max_ = 10 ** 7


# def count_prime(n):
#     prim = array('i', [0] * (n + 1))

#     for i in range(2, n + 1):
#         if not prim[i]:
#             for j in range(i, n + 1, i):
#                 prim[j] = i
#     return prim


# def prime_factor(x):
#     fac = []
#     while x > 1:
#         div = prim[x]
#         fac.append(div)

#         while x % div == 0:
#             x //= div
#     return fac
# prim=count_prime(max_)
# prime = [True for i in range(5*10**5 + 1)]
# def SieveOfEratosthenes(n):

#     p = 2
#     while (p * p <= n):

#         # If prime[p] is not changed, then it is a prime
#         if (prime[p] ==True):
#             prime[p]=p
#             # Update all multiples of p
#             for i in range(p ** 2, n + 1, p):
#                 prime[i] = p
#         p += 1
#     prime[0]= 0
#     prime[1]= 1
# SieveOfEratosthenes(5*10**5)
# # print(sum(el==True for el in prime))
# MOD = 998244353
# nmax = (2*(10**5))+2

# fact = [1] * (nmax+1)
# for i in range(2, nmax+1):
#     fact[i] = fact[i-1] * i % MOD

# inv = [1] * (nmax+1)
# for i in range(2, nmax+1):
#     inv[i] = pow(fact[i], MOD-2, MOD)


# def C(n, m):
#     return fact[n] * inv[m] % MOD * inv[n-m] % MOD if 0 <= m <= n else 0

# import sys
# import math
# mod = 10**7+1


# LI=lambda:[int(k) for k in input().split()]
# input = lambda: sys.stdin.readline().rstrip()
# IN=lambda:int(input())
# S=lambda:input()
# r=range

# fact=[i for i in r(mod)]
# for i in reversed(r(2,int(mod**0.5))):
#     i=i**2
#     for j in range(i,mod,i):
#         if fact[j]%i==0:
#             fact[j]//=i

from collections import Counter
from functools import lru_cache
from collections import deque


def main():
    from heapq import heappush, heappop, heapify

    # class SegmentTree:
    #     def __init__(self, data, default=0, func=max):
    #     self._default = default
    #     self._func = func
    #     self._len = len(data)
    #     self._size = _size = 1 << (self._len - 1).bit_length()

    #     self.data = [default] * (2 * _size)
    #     self.data[_size:_size + self._len] = data
    #     for i in reversed(range(_size)):
    #         self.data[i] = func(self.data[i + i], self.data[i + i + 1])

    # def __delitem__(self, idx):
    #     self[idx] = self._default

    # def __getitem__(self, idx):
    #     return self.data[idx + self._size]

    # def __setitem__(self, idx, value):
    #     idx += self._size
    #     self.data[idx] = value
    #     idx >>= 1
    #     while idx:
    #         self.data[idx] = self._func(self.data[2 * idx], self.data[2 * idx + 1])
    #         idx >>= 1

    # def __len__(self):
    #     return self._len

    # def query(self, start, stop):
    #     """func of data[start, stop)"""
    #     start += self._size
    #     stop += self._size
    #     if start==stop:
    #         return self._default
    #     res_left = res_right = self._default
    #     while start < stop:
    #         if start & 1:
    #             res_left = self._func(res_left, self.data[start])
    #             start += 1
    #         if stop & 1:
    #             stop -= 1
    #             res_right = self._func(self.data[stop], res_right)
    #         start >>= 1
    #         stop >>= 1

    #     return self._func(res_left, res_right)

    # def __repr__(self):
    #     return "SegmentTree({0})".format(self.data)
    import bisect, math

    #  ---------------------------------------------------------
    class SortedList:
        BUCKET_RATIO = 50
        REBUILD_RATIO = 170

        def __init__(self, buckets):
            buckets = list(buckets)
            buckets = sorted(buckets)
            self._build(buckets)

        def __iter__(self):
            for i in self.buckets:
                for j in i:
                    yield j

        def __reversed__(self):
            for i in reversed(self.buckets):
                for j in reversed(i):
                    yield j

        def __len__(self):
            return self.size

        def __contains__(self, x):
            if self.size == 0:
                return False
            bucket = self._find_bucket(x)
            i = bisect.bisect_left(bucket, x)
            return i != len(bucket) and bucket[i] == x

        def __getitem__(self, x):
            if x < 0:
                x += self.size
            if x < 0:
                raise IndexError
            for i in self.buckets:
                if x < len(i):
                    return i[x]
                x -= len(i)
            raise IndexError

        def _build(self, buckets=None):
            if buckets is None:
                buckets = list(self)
            self.size = len(buckets)
            bucket_size = int(math.ceil(math.sqrt(self.size / self.BUCKET_RATIO)))
            tmp = []
            for i in range(bucket_size):
                t = buckets[
                    (self.size * i)
                    // bucket_size : (self.size * (i + 1))
                    // bucket_size
                ]
                tmp.append(t)
            self.buckets = tmp

        def _find_bucket(self, x):
            for i in self.buckets:
                if x <= i[-1]:
                    return i
            return i

        def add(self, x):
            # O(√N)
            if self.size == 0:
                self.buckets = [[x]]
                self.size = 1
                return True

            bucket = self._find_bucket(x)
            bisect.insort(bucket, x)
            self.size += 1
            if len(bucket) > len(self.buckets) * self.REBUILD_RATIO:
                self._build()
            return True

        def remove(self, x):
            # O(√N)
            if self.size == 0:
                return False
            bucket = self._find_bucket(x)
            i = bisect.bisect_left(bucket, x)
            if i == len(bucket) or bucket[i] != x:
                return False
            bucket.pop(i)
            self.size -= 1
            if len(bucket) == 0:
                self._build()
            return True

        def lt(self, x):
            # less than < x
            for i in reversed(self.buckets):
                if i[0] < x:
                    return i[bisect.bisect_left(i, x) - 1]

        def le(self, x):
            # less than or equal to <= x
            for i in reversed(self.buckets):
                if i[0] <= x:
                    return i[bisect.bisect_right(i, x) - 1]

        def gt(self, x):
            # greater than > x
            for i in self.buckets:
                if i[-1] > x:
                    return i[bisect.bisect_right(i, x)]

        def ge(self, x):
            # greater than or equal to >= x
            for i in self.buckets:
                if i[-1] >= x:
                    return i[bisect.bisect_left(i, x)]

        def index(self, x):
            # the number of elements < x
            ans = 0
            for i in self.buckets:
                if i[-1] >= x:
                    return ans + bisect.bisect_left(i, x)
                ans += len(i)
            return ans

        def index_right(self, x):
            # the number of elements < x
            ans = 0
            for i in self.buckets:
                if i[-1] > x:
                    return ans + bisect.bisect_right(i, x)
                ans += len(i)
            return ans

    class IntKeyDict(dict):
        from random import randrange

        rand = randrange(1 << 62)

        def __setitem__(self, k, v):
            super().__setitem__(k ^ self.rand, v)

        def __getitem__(self, k):
            return super().__getitem__(k ^ self.rand)

        def __contains__(self, k):
            return super().__contains__(k ^ self.rand)

        def __repr__(self):
            return str({k: v for k, v in self.items()})

        def get(self, k, default=None):
            return super().get(k ^ self.rand, default)

        def keys(self):
            return [k ^ self.rand for k in super().keys()]

        def items(self):
            return [(k ^ self.rand, v) for k, v in super().items()]

        # --------------------------------------------------------

    r, n = map(int, input().split())
    a = [[0, 1, 1]] + [list(map(int, input().split())) for _ in range(n)]
    memo = [0] * (n + 1)
    ma = [0] * (n + 1)
    for i, (t, x, y) in enumerate(a[1:], 1):
        ix = i - 1
        curr = -(1 << 30)
        all = t - (max(x, 500 - x) + max(y, 500 - x))
        while ix >= 0:
            if (
                memo[ix] > curr
                and abs(a[ix][1] - x) + abs(a[ix][2] - y) <= t - a[ix][0]
            ):
                curr = memo[ix]
            if all >= abs(a[ix][0]):
                curr = max(ma[ix], curr)
                break
            ix -= 1
        memo[i] = curr + 1
        ma[i] = max(ma[i - 1], memo[i])
    print(ma[-1])


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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


if __name__ == "__main__":
    main()
