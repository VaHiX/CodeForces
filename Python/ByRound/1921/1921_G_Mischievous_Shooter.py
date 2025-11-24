# Problem: CF 1921 G - Mischievous Shooter
# https://codeforces.com/contest/1921/problem/G

"""
Algorithm: 
The problem involves finding the maximum number of targets that can be hit by a single shot in four diagonal directions (right-down, left-down, left-up, right-up). The shotgun has a Manhattan distance constraint k.

Approach:
1. For each of the four diagonal directions, we compute the maximum targets that can be hit.
2. We preprocess the grid to compute prefix sums for efficient range sum queries.
3. Using dynamic programming, we calculate the number of targets hit for each possible starting position in each direction.
4. The solution uses rotation and reflection of the grid to handle all four directions with a common code path.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

The algorithm works by:
1. Preprocessing prefix sums for rows, columns, and diagonals
2. Using sliding window technique to calculate targets hit for each starting point
3. Applying transformations (rotation/reflection) to handle all four directions
"""

import os
import sys
from io import BytesIO, IOBase

INF = float("inf")
BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
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
input = sys.stdin.buffer.readline

ask = lambda *x: print("?", *x, flush=True)
reply = lambda *x: print("!", *x, flush=True)

RI = lambda: int(sys.stdin.readline())
RF = lambda: float(sys.stdin.readline())
RS = lambda: sys.stdin.readline().strip()
RFF = lambda: map(float, sys.stdin.readline().split())
RII = lambda: map(int, sys.stdin.readline().split())
RSS = lambda: map(str, sys.stdin.readline().strip().split())
RIL = lambda: list(RII())
RFL = lambda: list(RFF())
RSL = lambda: list(RSS())

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


def main():
    test = RI()

    for _ in range(test):
        n, m, k = RII()
        a = []
        for i in range(n):
            s = RS()
            a.append([1 if s[j] == "#" else 0 for j in range(m)])

        ans = 0

        def solve():
            nonlocal ans, n, m
            # Initialize prefix sum arrays
            f1 = [[0] * (n + 2) for i in range(m)]  # column-wise prefix sums
            f2 = [[0] * (m + 2) for i in range(n)]  # row-wise prefix sums
            g = [[0] * (n + 2) for i in range(m + n + 2)]  # diagonal prefix sums
            
            # Compute column-wise prefix sums
            for j in range(m):
                for i in range(n):
                    f1[j][i] = f1[j][i - 1] + a[i][j]
            
            # Compute row-wise prefix sums
            for i in range(n):
                for j in range(m):
                    f2[i][j] = f2[i][j - 1] + a[i][j]
            
            # Compute diagonal prefix sums
            for x in range(m + n - 1):
                for i in range(max(0, x - (m - 1)), min(n, x + 1)):
                    j = x - i
                    g[x][i] = g[x][i - 1] + a[i][j]

            # Dynamic programming to calculate hit counts
            dp = [[0] * (m + 1) for i in range(n)]
            
            # Initialize corner cases
            for i in range(min(n, k + 1)):
                for j in range(min(m, k + 1 - i)):
                    dp[0][0] += a[i][j]

            # Compute prefix sums for first row
            i = 0
            for j in range(m - 1):
                val = (
                    g[i + j + k + 1][min(n - 1, i + k)] - g[i + j + k + 1][i - 1]
                    if i + j + k + 1 <= n + m - 2
                    else 0
                ) - (f1[j][min(i + k, n - 1)] - f1[j][i - 1])
                dp[0][j + 1] = dp[0][j] + val
            
            # Compute prefix sums for remaining positions
            for j in range(m):
                for i in range(n - 1):
                    val = (
                        g[i + j + k + 1][min(n - 1, i + k + 1)] - g[i + j + k + 1][i]
                        if i + j + k + 1 <= n + m - 2
                        else 0
                    ) - (f2[i][min(j + k, m - 1)] - f2[i][j - 1])
                    dp[i + 1][j] = dp[i][j] + val

            # Find maximum hits across all positions and directions
            for i in range(n):
                for j in range(m):
                    ans = max(ans, dp[i][j])

        # Handle case where grid is wider than tall by swapping
        oa = []
        import copy

        if n > m:
            for j in range(m):
                b = []
                for i in range(n):
                    b.append(a[i][j])
                oa.append(b)
            n, m = m, n
            a = copy.deepcopy(oa)
        else:
            oa = copy.deepcopy(a)

        # Apply all four rotations/reflections to handle different shooting directions
        solve()
        for i in range(n):
            for j in range(m):
                a[i][j] = oa[n - 1 - i][j]
        solve()
        for i in range(n):
            for j in range(m):
                a[i][j] = oa[n - 1 - i][m - 1 - j]
        solve()
        for i in range(n):
            for j in range(m):
                a[i][j] = oa[i][m - 1 - j]
        solve()

        print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/