# Problem: CF 1866 D - Digital Wallet
# https://codeforces.com/contest/1866/problem/D

"""
Algorithm: Dynamic Programming with Sliding Window Optimization
Time Complexity: O(N * M * K)
Space Complexity: O(M * K)

This problem uses dynamic programming to find the maximum sum of elements that can be collected
by choosing elements from arrays under specific constraints. In each operation, we select an element
from an array and add its value to the wallet, then set that element to zero. The selection must
follow a sliding window constraint where elements chosen in consecutive operations must be within
a window of size K.

The DP state dp[i][j] represents the maximum sum obtainable after i operations, with the last
operation being at position j in the current window of size K.

We use a sliding window approach with prefix sums to efficiently compute the maximum values
that can be chosen at each step.
"""

import io
import os
import sys
from itertools import accumulate

MOD = 998244353
inf = 1 << 60


def solve():
    n, m, k = read_int_tuple()  # Read number of arrays, array size, and window size
    A = [read_int_list() for _ in range(n)]  # Read all arrays
    # dp[i][j] = max sum after i operations, with last operation at position j in window
    dp = [[-inf] * k for _ in range(m + 1)]  # Initialize DP table with negative infinity
    dp[0][0] = 0  # Base case: 0 operations, 0 money
    for i in range(m):  # For each position in arrays
        # Get all elements at position i from all arrays and sort them in descending order
        P = sorted((A[j][i] for j in range(n)), reverse=True)
        P = list(accumulate(P))  # Compute prefix sums for efficient range sum queries
        for j in range(k):  # For each possible position in window
            for p in range(n + 1):  # Try choosing p elements from different arrays at this step
                j2 = j - p + 1  # New window position based on how many elements we select
                if j2 >= 0 and j2 < k:  # Ensure new position is valid
                    # Update DP state with maximum of current value and new value
                    dp[i + 1][j2] = max(
                        dp[i + 1][j2], dp[i][j] + (P[p - 1] if p else 0)
                    )

    print(dp[m][k - 1])  # Maximum sum after all operations


def main():
    # Number of test cases (always 1 in this case)
    T = 1
    for t in range(T):
        solve()


BUFSIZE = 8192


class FastIO(io.IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = io.BytesIO()
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


class IOWrapper(io.IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


def print(*args, **kwargs):
    """Prints the values to a stream, or to sys.stdout by default."""
    sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
    at_start = True
    for x in args:
        if not at_start:
            file.write(sep)
        file.write(str(x))
        at_start = False
    file.write(kwargs.pop("end", "\n"))
    if kwargs.pop("flush", False):
        file.flush()


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

input = lambda: sys.stdin.readline().rstrip("\r\n")


def read_int_list():
    return list(map(int, input().split()))


def read_ints_minus_one():
    return [int(x) - 1 for x in input().split()]


def read_int_tuple():
    return map(int, input().split())


def read_encode_str(d=97):
    return [ord(x) - d for x in input()]


def read_graph(n: int, m: int, d=1):
    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int, input().split())
        g[u - d].append(v - d)
        g[v - d].append(u - d)
    return g


def read_grid(m: int):
    return [input() for _ in range(m)]


def read_int():
    return int(input())


read_str = input


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/