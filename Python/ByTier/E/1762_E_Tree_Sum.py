# Problem: CF 1762 E - Tree Sum
# https://codeforces.com/contest/1762/problem/E

"""
Algorithm: Tree Sum
Purpose: Calculate the sum of d(1,n) over all good edge-weighted trees with n vertices.
Good tree definition: 
- Each edge has weight 1 or -1
- For each vertex i, the product of edge weights on all edges incident to i is -1

Time Complexity: O(n)
Space Complexity: O(n)

Key insights:
1. The number of good trees is 2^(n-1) * (n-2)!, as there's a bijection between good trees and certain combinations
2. The formula is derived based on enumeration and combinatorics:
   - For a tree with n vertices, we compute sum over all possible paths from 1 to n
   - The answer involves alternating signs and combinatorial calculations
3. The result is computed modulo 998244353

This uses precomputed factorials and modular inverse for efficient combination calculation.
"""

import os
import sys
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


def exgcd(a, b):
    if b == 0:
        return 1, 0, a
    else:
        x, y, q = exgcd(b, a % b)
        x, y = y, (x - (a // b) * y)
        return x, y, q


def ModReverse(a, p):
    x, y, q = exgcd(a, p)
    return x % p


k, mod = 10**5 * 5, 998244353
fac = [1]
for i in range(1, k + 1):
    fac.append(fac[-1] * i % mod)

k_inv = k
fac_inv = [0] * (k_inv + 1)
fac_inv[k_inv] = ModReverse(fac[k_inv], mod)
for i in range(k_inv - 1, -1, -1):
    fac_inv[i] = fac_inv[i + 1] * (i + 1) % mod


def comb(x, y):
    if y < 0 or y > x:
        return 0
    return fac[x] * fac_inv[y] * fac_inv[x - y] % mod


n = II()
if n % 2:  # If n is odd, no good tree exists
    print(0)
    exit()

ans = 0
for i in range(1, n):  # Loop through all possible values
    # Compute the contribution of each term in the sum
    ans += (
        (-1) ** i
        * comb(n - 2, i - 1)  # Combinatorial coefficient
        * pow(i, i - 1, mod)  # i^(i-1) mod mod
        * pow(n - i, n - i - 1, mod)  # (n-i)^(n-i-1) mod mod
        % mod
    )
    ans %= mod  # Keep result within mod
print(ans)


# https://github.com/VaHiX/CodeForces/