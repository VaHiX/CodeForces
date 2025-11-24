# Problem: CF 1765 C - Card Guessing
# https://codeforces.com/contest/1765/problem/C

'''
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n*k^2)
Space Complexity: O(n*k)

This code calculates the expected number of correct guesses Monocarp makes when drawing cards from a shuffled deck.
The approach uses dynamic programming to precompute probabilities and then computes the expectation using combinatorics.
'''

import os
import sys
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 4096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


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


inf = float("inf")


class Factorial:
    def __init__(self, N, mod) -> None:
        N += 1
        self.mod = mod
        self.f = [1 for _ in range(N)]
        self.g = [1 for _ in range(N)]
        for i in range(1, N):
            self.f[i] = self.f[i - 1] * i % self.mod
        self.g[-1] = pow(self.f[-1], mod - 2, mod)
        for i in range(N - 2, -1, -1):
            self.g[i] = self.g[i + 1] * (i + 1) % self.mod

    def fac(self, n):
        return self.f[n]

    def fac_inv(self, n):
        return self.g[n]

    def comb(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

    def perm(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[n - m] % self.mod

    def catalan(self, n):
        return (self.comb(2 * n, n) - self.comb(2 * n, n - 1)) % self.mod

    def inv(self, n):
        return self.f[n - 1] * self.g[n] % self.mod


mod = 998244353
fact = Factorial(2000, mod)


def getRes(i):
    # DP table where dp[a][b] represents number of ways to have 'a' suits with 'b' cards in the last k cards
    dp = [[0] * (k + 1) for _ in range(5)]
    dp[0][0] = 1  # Initially, no suits, no cards
    for a in range(4):
        for b in range(k + 1):
            for c in range(i, n + 1):
                if b + c > k:
                    break  # Exceeds k cards
                if dp[a][b]:
                    # Add new combinations of cards with 'a' suits and 'b' cards
                    dp[a + 1][b + c] += (
                        dp[a][b] * fact.perm(b + c, c) % mod * fact.comb(n, c) % mod
                    )
                    dp[a + 1][b + c] %= mod
    return dp[-1]  # Return the last row which contains total combinations


n, k = MII()
note = []
for i in range(k // 4 + 1):
    note.append(getRes(i))

# Compute prefix sums to get the differences
for i in range(k // 4):
    for j in range(k + 1):
        note[i][j] -= note[i + 1][j]
        note[i][j] %= mod


def calcExpectation(cards_num):
    # Calculate expectation for drawing 'cards_num' cards
    cnt = 0
    for minimum_count in range(cards_num // 4 + 1):
        # Multiply each probability by the number of remaining cards of the suit
        cnt += (
            note[minimum_count][cards_num]
            * (n - minimum_count)
            * fact.inv(4 * n - cards_num)
        )
        # Take modulo to prevent overflow
        cnt %= mod
    # Multiply by factorials to normalize the probabilities
    cnt *= fact.fac(4 * n - cards_num) * fact.fac_inv(4 * n)
    cnt %= mod
    return cnt


res = 0
# Iterate through all possible number of cards drawn before reaching k
for cards_num in range(k):
    res += calcExpectation(cards_num)
    res %= mod
# Handle case when cards drawn >= k
if k < 4 * n:
    res += calcExpectation(k) * (4 * n - k)
    res %= mod
print(res)


# https://github.com/VaHiX/CodeForces/