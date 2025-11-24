# Problem: CF 2041 H - Sheet Music
# https://codeforces.com/contest/2041/problem/H

"""
Code Purpose:
This code calculates the number of distinct musical sequences of length n
using pitches from 1 to k, where two sequences are considered equivalent
if their consecutive pitch relationships are the same. This is solved using dynamic programming
and combinatorics to count unique "sign patterns" (increasing, decreasing, equal) and
then multiply by combinations of how to assign pitches to these patterns.

Algorithms/Techniques:
1. Dynamic Programming to count sign patterns of size up to N.
2. Preprocessing factorials for modular inverse and binomial coefficients.
3. Combinatorial counting to distribute pitches among patterns.

Time Complexity: O(N)
Space Complexity: O(N)
"""

import inspect
import os
import sys
from io import BytesIO, IOBase

MOD = 998244353

inf = float("inf")
ninf = float("-inf")
fmin = lambda x, y: x if x < y else y
fmax = lambda x, y: x if x > y else y


def debug(*expressions):
    names = inspect.currentframe().f_back.f_locals
    for expr in expressions:
        for name, val in names.items():
            if val is expr:
                print(f"{name }= {expr }")
                break
        else:
            print(f"[expr]= {expr }")
    if len(expressions) > 1:
        print()


MX = 10**6 + 123
fac = [1] * (MX + 1)
for i in range(2, MX + 1):
    fac[i] = fac[i - 1] * i % MOD

ifac = fac[:]
ifac[-1] = pow(fac[-1], MOD - 2, MOD)
for i in range(MX - 1, -1, -1):
    ifac[i] = ifac[i + 1] * (i + 1) % MOD


def binom(n, k):
    if k < 0 or k > n:
        return 0
    return fac[n] * ifac[n - k] % MOD * ifac[k] % MOD


def solve():
    N, K = rlist()
    K = min(K, N + 1)
    if N == 1:
        return 1

    # dp[i] represents number of sign patterns of length i+1
    dp = [0] * N
    sdp = [0] * N
    sdp[0] = dp[0] = 1

    # Build up dp array using prefix sums, accounting for maximum pitch difference K
    for i in range(1, N):
        dp[i] = sdp[i - 1]
        if i >= K:
            dp[i] -= sdp[i - K]
        sdp[i] = sdp[i - 1] + dp[i]
        dp[i] %= MOD
        sdp[i] %= MOD
        
    # Multiply all dp values by 2 to account for both ascending and descending sequences
    for i in range(1, N):
        dp[i] = 2 * dp[i] % MOD

    ans = 0
    # Iterate over all possible lengths of "natural" sequences (sign patterns)
    for sig_length in range(N):
        natural = dp[sig_length]
        zeroes = N - sig_length - 1   # Number of "equal" pairs (zeroes in the sequence)
        part = natural * binom(N - 1, zeroes)  # Number of ways to place these equal pairs

        ans += part
        ans %= MOD
    return ans


def main():
    T = 1

    for tc in range(1, 1 + T):
        ans = solve()

        print(ans)


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
input = lambda: sys.stdin.readline().rstrip("\r\n")
rint = lambda: int(input())
rlist = lambda: list(map(int, input().split()))
rgrid = lambda n: [rlist() for _ in range(n)]


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/