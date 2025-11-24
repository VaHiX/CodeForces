# Problem: CF 2048 F - Kevin and Math Class
# https://codeforces.com/contest/2048/problem/F

"""
Algorithm: Min Cartesian Tree with Dynamic Programming
Techniques: 
- Min Cartesian Tree construction for segment optimization
- Dynamic Programming with memoization on tree structure
- Segment-based operations with ceiling division

Time Complexity: O(N * log(N) + N * Z) where Z = 62 (number of bits)
Space Complexity: O(N * Z) for DP table and auxiliary structures

Approach:
1. Build a min Cartesian tree for array B to identify optimal segments
2. Use dynamic programming on the tree to find minimal operations needed
3. For each node in the tree, compute minimum operations to reduce all elements in its subtree to 1
4. The answer is the minimum k such that dp[root][k] = 1
"""

import os
import sys
from io import BytesIO, IOBase

from _collections import deque

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


def min_cartesian_tree(arr):
    root = arr.index(min(arr))  # Find index of minimum element as root
    left = [-1] * len(arr)      # Left child in cartesian tree
    q = deque()
    for pos in range(len(arr)):
        while q and arr[pos] < arr[q[-1]]:
            left[pos] = q.pop()   # Pop elements greater than current
        q.append(pos)
    right = [len(arr)] * len(arr)  # Right child in cartesian tree
    q = deque()
    for pos in range(len(arr) - 1, -1, -1):
        while q and arr[pos] <= arr[q[-1]]:
            right[pos] = q.pop()
        q.append(pos)
    return root, left, right


def solve():
    start, left, right = min_cartesian_tree(B)
    seen = [-1] * N
    q = deque([start])
    seen[start] = 0
    dp = [[1 << 62 for _ in range(Z)] for _ in range(N + 2)]
    for k in range(Z):
        dp[N][k] = dp[-1][k] = 1  # Base case: out of bounds are done
    while q:
        n = q[-1]  # Current node
        chs = [left[n], right[n]]  # Children
        nb = seen[n]
        if nb == len(chs):
            q.pop()
            ql = deque([])
            qr = deque([])
            for k in range(Z):
                if k > 0:
                    # Compute ceil(a[i] / b[i]) for current level of operations
                    dp[n][k] = (dp[n][k - 1] + B[n] - 1) // B[n]
                ql.append(dp[left[n]][k])
                qr.append(dp[right[n]][k])
                qmx = ql if ql[0] >= qr[0] else qr
                dp[n][k] = min(dp[n][k], max(A[n], qmx[0]))
                qmx.popleft()
        else:
            ch = chs[nb]
            if 0 <= ch <= N - 1 and seen[ch] == -1:
                seen[ch] = 0
                q.append(ch)
            seen[n] += 1
    for k in range(Z):
        if dp[start][k] == 1:
            return str(k)


Z = 62  # Number of bits in a 64-bit integer
for test in range(1, ui() + 1):
    N = ui()
    A = li()
    B = li()
    print(solve())
file.close()


# https://github.com/VaHiX/CodeForces/