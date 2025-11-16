# Problem: CF 1740 F - Conditional Mix
# https://codeforces.com/contest/1740/problem/F

"""
Algorithm: Dynamic Programming with Combinatorial Logic
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This problem involves counting the number of distinct multisets that can be formed
by merging sets of elements from an array. The key insight is to use dynamic programming
where dp[i][j] represents the number of ways to form a multiset with exactly j total elements
using i distinct group sizes. 

The algorithm works by:
1. Counting frequency of each element
2. Preprocessing cumulative counts
3. Using dynamic programming to compute combinations
4. Summing up all valid configurations

The approach uses the fact that we can merge sets of same elements, and we want to count
all possible multisets that can result from such operations.
"""

import os
import sys
from collections import Counter
from io import BytesIO, IOBase

BUFSIZE = 4096
inf = float("inf")


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


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


n = II()
nums = LII()
mod = 998244353
dp = [[0] * 2001 for _ in range(2001)]
dp[0][0] = 1
cnt = Counter()
note = [0] * (n + 1)
for num in nums:
    cnt[num] += 1
    note[cnt[num]] += 1

for i in range(1, n + 1):
    note[i] += note[i - 1]

for i in range(n, 0, -1):
    j = 1
    while i * j <= n:
        for k in range(i * j, note[j] + 1):
            dp[j][k] = (dp[j][k] + dp[j - 1][k - i]) % mod
        j += 1

ans = 0
for i in range(1, n + 1):
    ans += dp[i][n]
    ans %= mod
print(ans)


# https://github.com/VaHiX/CodeForces/