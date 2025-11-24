# Problem: CF 1427 C - The Hard Work of Paparazzi
# https://codeforces.com/contest/1427/problem/C

"""
Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n * sqrt(n) * log(n))
Space Complexity: O(n)

This solution uses dynamic programming to find the maximum number of celebrities
that can be photographed. The key insight is to optimize the transition between
celebrities by using a sorted data structure to efficiently query the best previous
celebrity that can be reached before the current one.

The approach:
1. Sort celebrities by time
2. For each celebrity, find the maximum number of celebrities that can be visited
   before it using dynamic programming
3. Use a sorted data structure to speed up the search for valid previous celebrities
4. The state `memo[i]` represents the maximum number of celebrities that can be
   photographed ending at the i-th celebrity
5. `ma[i]` maintains the maximum value of `memo` up to index i

The algorithm is optimized by considering only a subset of previous celebrities
and using the sorted data structure for efficient queries.
"""

import os
import sys
from io import BytesIO, IOBase


def main():
    import bisect
    import math

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
            for i in reversed(self.buckets):
                if i[0] < x:
                    return i[bisect.bisect_left(i, x) - 1]

        def le(self, x):
            for i in reversed(self.buckets):
                if i[0] <= x:
                    return i[bisect.bisect_right(i, x) - 1]

        def gt(self, x):
            for i in self.buckets:
                if i[-1] > x:
                    return i[bisect.bisect_right(i, x)]

        def ge(self, x):
            for i in self.buckets:
                if i[-1] >= x:
                    return i[bisect.bisect_left(i, x)]

        def index(self, x):
            ans = 0
            for i in self.buckets:
                if i[-1] >= x:
                    return ans + bisect.bisect_left(i, x)
                ans += len(i)
            return ans

        def index_right(self, x):
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


# https://github.com/VaHiX/CodeForces/