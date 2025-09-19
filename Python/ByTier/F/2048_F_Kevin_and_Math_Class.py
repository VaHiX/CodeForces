# Contest 2048, Problem F: Kevin and Math Class
# URL: https://codeforces.com/contest/2048/problem/F

import sys
import os
from io import BytesIO, IOBase
from itertools import chain
from _collections import deque

# region fastio
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


if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

file = sys.stdin
if os.environ.get("USER") == "loic":
    file = open("data.in")

line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int, line())
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))
#######################################################################


def min_cartesian_tree(arr):
    root = arr.index(min(arr))

    left = [-1] * len(arr)
    right = [len(arr)] * len(arr)
    q = deque()
    for pos in range(len(arr)):
        while q and arr[pos] < arr[q[-1]]:
            left[pos] = q.pop()
        if q:
            right[q[-1]] = pos
        q.append(pos)

    return root, left, right


def solve():

    start, left, right = min_cartesian_tree(B)

    seen = [-1] * N
    q = deque([start])
    seen[start] = 0

    dp = [[1 << 62 for _ in range(Z)] for _ in range(N + 2)]
    for k in range(Z):
        dp[N][k] = dp[-1][k] = 1

    while q:
        n = q[-1]

        chs = [left[n], right[n]]
        nb = seen[n]
        if nb == len(chs):
            q.pop()

            i = 0
            j = 0
            for k in range(Z):
                if k > 0:
                    dp[n][k] = (dp[n][k - 1] + B[n] - 1) // B[n]
                mx = -1
                if dp[left[n]][i] >= dp[right[n]][j]:
                    mx = dp[left[n]][i]
                    i += 1
                else:
                    mx = dp[right[n]][j]
                    j += 1
                dp[n][k] = min(dp[n][k], max(A[n], mx))

        else:
            ch = chs[nb]
            if 0 <= ch <= N - 1 and seen[ch] == -1:
                seen[ch] = 0
                q.append(ch)
            seen[n] += 1

    for k in range(Z):
        if dp[start][k] == 1:
            return str(k)


Z = 62

for test in range(1, ui() + 1):
    N = ui()
    A = li()
    B = li()

    print(solve())

file.close()
