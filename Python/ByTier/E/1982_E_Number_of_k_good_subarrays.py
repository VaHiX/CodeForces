# Problem: CF 1982 E - Number of k-good subarrays
# https://codeforces.com/contest/1982/problem/E

"""
Number of k-good subarrays

Approach:
This problem uses dynamic programming with digit DP (Digit Dynamic Programming) technique.
We precompute dp[i][j] which represents the number of valid subarrays ending at position i with at most j bits set.
Then, for each query, we compute the result by traversing the binary representation of N from most significant bit to least,
using precomputed dp values to count valid subarrays.

Time Complexity: O(1) for each test case after precomputation (since k <= 60 and n <= 10^18)
Space Complexity: O(1) as we use fixed size arrays (61x61) for dp table
"""

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


def solve():
    # Result to be returned
    res = 0

    # Current number of allowed bits in k-good subarrays
    c = K + 1
    
    # Iterate from most significant bit to least significant bit
    for i in range(60, -1, -1):
        # Check if the i-th bit is set in N
        if (N >> i) & 1:
            # If current bit is set and i < c, we compute contribution of subarrays
            if i < c:
                tr = N & ((1 << (i + 1)) - 1)
                # Add triangular number contribution 
                res = (res + tr * (tr + 1) // 2) % MOD
                break

            # Add the precomputed dp value to result
            res = (res + dp[i][c]) % MOD
            c -= 1
        # If all bits have been processed, break
        if c == 0:
            break

    return str(res)


MOD = 10**9 + 7


# Precompute dp table for all possible combinations of bits and allowed ones
# dp[i][j] represents number of valid subarrays ending at position i with at most j bits set
dp = [[0 for _ in range(61)] for _ in range(61)]

# Base case: dp[i][0] = 1 (only empty subarrays have 0 bits set)
for i in range(61):
    dp[i][0] = 1
    
    # dp[i][i] = triangular sum for full bit length i
    dp[i][i] = (((1 << i) - 1) * (1 << i) // 2) % MOD

# Fill the dp table using dynamic programming approach
for i in range(1, 61):
    for j in range(1, i):
        # Calculate dp[i][j] by summing values from previous state using specific logic
        for k in range(i - 1, i - j - 1, -1):
            dp[i][j] = (dp[i][j] + dp[k][k - (i - j - 1)]) % MOD


# Process all test cases
for test in range(1, ui() + 1):
    N, K = mi()

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/