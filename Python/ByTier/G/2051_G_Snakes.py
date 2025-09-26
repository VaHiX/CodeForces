# Contest 2051, Problem G: Snakes
# URL: https://codeforces.com/contest/2051/problem/G

import sys
import os
from io import BytesIO, IOBase
from random import randint, choice
import time

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


def conv(a, b):
    return a * N + b


def solve():

    mn = []
    ext = [0 for _ in range(N)]

    for i in range(N):
        diff = [0 for _ in range(N)]
        arr = [0 for _ in range(N)]
        for q in range(Q):
            if A[q][0] == i and A[q][1] == 1:
                for k in range(N):
                    diff[k] -= 1
                    arr[k] = min(arr[k], diff[k])
                ext[i] += 1
            elif A[q][1] == -1:
                diff[A[q][0]] += 1

        mn.append(arr)

    mn = [val for row in mn for val in row]

    dp = [Z for _ in range(N * (1 << N))]
    for i in range(N):
        dp[conv(1 << i, i)] = 0

    for mask in range(1, 1 << N):
        state = [[] for _ in range(2)]
        for i in range(N):
            state[(mask >> i) & 1].append(i)
        for i in state[1]:
            for j in state[0]:
                idx = conv(mask | (1 << j), j)
                val = dp[conv(mask, i)] - mn[conv(i, j)]
                if val < dp[idx]:
                    dp[idx] = val

    res = N + min(dp[conv((1 << N) - 1, i)] + ext[i] for i in range(N))

    return str(res)


Z = 10**18

for test in range(1, 1 + 1):
    N, Q = mi()

    A = []
    for i in range(Q):
        data = line()
        A.append((int(data[0]) - 1, 1 if data[1] == "+" else -1))

    print(solve())

file.close()
