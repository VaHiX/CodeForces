# Problem: CF 1983 E - I Love Balls
# https://codeforces.com/contest/1983/problem/E

"""
Algorithm: Expected Score Calculation for Alice and Bob
Techniques: Mathematical expectation, modular arithmetic, prefix sums

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input storage)

This solution calculates the expected scores for Alice and Bob in a game where:
- There are n balls, k of which are special
- Players alternate turns picking balls
- If a special ball is picked, the same player takes the next turn
- If a non-special ball is picked, the other player takes the next turn
- The goal is to compute expected scores for both players modulo 10^9 + 7

The key insight is that we can compute:
1. Probability that Alice picks any specific ball
2. Probability that Bob picks any specific ball
3. Use linearity of expectation to compute total expected scores

The code uses modular inverse to compute probabilities and applies the mathematical expectation formula.
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

printf = lambda x: sys.stdout.write(str(x) + " ")
printa = lambda x: sys.stdout.write("ans:" + str(x) + "\n")
printt = lambda *x: print("test:", *x)
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


class TreeArray:
    def __init__(self, a):
        self.n = len(a)
        self.d = [0] * (self.n + 2)
        for p in range(1, self.n + 1):
            x = a[p - 1]
            while p <= self.n:
                self.d[p] += x
                p += self.lowbit(p)

    def lowbit(self, x):
        return x & -x

    def update(self, p, x):
        p += 1
        while p <= self.n:
            self.d[p] += x
            p += self.lowbit(p)

    def query(self, p):
        res = 0
        p += 1
        while p >= 1:
            res += self.d[p]
            p -= self.lowbit(p)
        return res


def main():
    test = RI()
    MOD = 10**9 + 7

    for _ in range(test):
        n, k = RII()
        a = RIL()
        if n == k:
            print(sum(a) % MOD, 0)
            continue
        # Calculate probability that alice picks a non-special ball
        pna = (
            ((n - k) // 2 if (n - k) % 2 == 0 else (n - k) // 2 + 1)
            * pow(n - k, -1, MOD)
            % MOD
        )
        # Calculate probability that alice picks a special ball  
        pa = (
            ((n - k + 1) // 2 if (n - k + 1) % 2 == 0 else (n - k + 1) // 2 + 1)
            * pow(n - k + 1, -1, MOD)
            % MOD
        )
        # Calculate expected score for Alice
        ans = 0
        for i in range(n):
            if i <= k - 1:
                # Special ball - use probability pa
                ans += pa * a[i]
            else:
                # Non-special ball - use probability pna
                ans += pna * a[i]
        ans %= MOD
        # Bob's expected score is total minus Alice's
        print(ans, (sum(a) - ans) % MOD)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/