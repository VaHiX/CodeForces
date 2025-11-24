# Problem: CF 1684 F - Diverse Segments
# https://codeforces.com/contest/1684/problem/F

"""
Algorithm: Diverse Segments
Approach:
- Compress the input array values to reduce the range of elements
- For each element, track the last occurrence and determine conflict points
- Use segment tree to efficiently query and update ranges
- Determine the minimal segment length required to resolve conflicts

Time Complexity: O(n log n + m log n)
Space Complexity: O(n)
"""

import bisect

mod = 998244353

import os
import sys
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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

import typing


class SegTree:
    def __init__(
        self,
        op: typing.Callable[[typing.Any, typing.Any], typing.Any],
        e: typing.Any,
        v: typing.Union[int, typing.List[typing.Any]],
    ) -> None:
        self._op = op
        self._e = e

        if isinstance(v, int):
            v = [e] * v

        self._n = len(v)
        self._log = self._n.bit_length()
        self._size = 1 << self._log
        self._d = [e] * (2 * self._size)

        for i in range(self._n):
            self._d[self._size + i] = v[i]
        for i in range(self._size - 1, 0, -1):
            self._update(i)

    def set(self, p: int, x: typing.Any) -> None:
        assert 0 <= p < self._n

        p += self._size
        self._d[p] = x
        for i in range(1, self._log + 1):
            self._update(p >> i)

    def get(self, p: int) -> typing.Any:
        assert 0 <= p < self._n

        return self._d[p + self._size]

    def prod(self, left: int, right: int) -> typing.Any:
        assert 0 <= left <= right <= self._n
        sml = self._e
        smr = self._e
        left += self._size
        right += self._size

        while left < right:
            if left & 1:
                sml = self._op(sml, self._d[left])
                left += 1
            if right & 1:
                right -= 1
                smr = self._op(self._d[right], smr)
            left >>= 1
            right >>= 1

        return self._op(sml, smr)

    def all_prod(self) -> typing.Any:
        return self._d[1]

    def max_right(self, left: int, f: typing.Callable[[typing.Any], bool]) -> int:
        assert 0 <= left <= self._n
        assert f(self._e)

        if left == self._n:
            return self._n

        left += self._size
        sm = self._e

        first = True
        while first or (left & -left) != left:
            first = False
            while left % 2 == 0:
                left >>= 1
            if not f(self._op(sm, self._d[left])):
                while left < self._size:
                    left *= 2
                    if f(self._op(sm, self._d[left])):
                        sm = self._op(sm, self._d[left])
                        left += 1
                return left - self._size
            sm = self._op(sm, self._d[left])
            left += 1

        return self._n

    def min_left(self, right: int, f: typing.Callable[[typing.Any], bool]) -> int:
        assert 0 <= right <= self._n
        assert f(self._e)

        if right == 0:
            return 0

        right += self._size
        sm = self._e

        first = True
        while first or (right & -right) != right:
            first = False
            right -= 1
            while right > 1 and right % 2:
                right >>= 1
            if not f(self._op(self._d[right], sm)):
                while right < self._size:
                    right = 2 * right + 1
                    if f(self._op(self._d[right], sm)):
                        sm = self._op(self._d[right], sm)
                        right -= 1
                return right + 1 - self._size
            sm = self._op(self._d[right], sm)

        return 0

    def _update(self, k: int) -> None:
        self._d[k] = self._op(self._d[2 * k], self._d[2 * k + 1])


INF = 1 << 31


def compress(mylist):
    B = list(set(mylist))
    B.sort()
    D = {v: i for i, v in enumerate(B)}
    return list(map(lambda v: D[v], mylist))


def solve():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    a = compress(a)  # Compress values to smaller range
    ma = max(a)
    prv = [-1] * (ma + 1)
    cnt = [[] for _ in range(ma + 1)]
    fli = [-1] * n
    now = -1
    for i in range(n):
        if prv[a[i]] == -1:
            prv[a[i]] = i
        else:
            now = max(now, prv[a[i]])
            prv[a[i]] = i
        fli[i] = now
        cnt[a[i]].append(i)
    mi = INF
    seg = SegTree(min, INF, n)
    for _ in range(m):
        l, r = map(int, input().split())
        if fli[r - 1] < l - 1:
            continue
        else:
            tmp = seg.get(r - 1)
            if tmp > l - 1:
                seg.set(r - 1, l - 1)
            idx = bisect.bisect_left(fli, l - 1)
            mi = min(mi, idx)
    if mi == INF:
        print(0)
        return
    ans = n - mi
    for i in range(n - 1)[::-1]:
        idx = bisect.bisect_right(cnt[a[i + 1]], i + 1)
        if idx != len(cnt[a[i + 1]]):
            tmp = seg.prod(cnt[a[i + 1]][idx], n)
            if tmp <= i + 1:
                break

        if idx > 1:
            tmp = seg.prod(i + 1, n)
            midx = bisect.bisect_left(cnt[a[i + 1]], tmp)
            if midx < len(cnt[a[i + 1]]):

                mi = min(mi, cnt[a[i + 1]][midx])
        ans = min(ans, i + 1 - mi)
    print(ans)
    return 0


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/