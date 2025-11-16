# Problem: CF 1817 C - Similar Polynomials
# https://codeforces.com/contest/1817/problem/C

"""
Algorithm: Polynomial Similarity Finding using Combinatorial Identities

This code solves the problem of finding an integer 's' such that B(x) ≡ A(x+s) (mod 10^9+7) 
for two similar polynomials A(x) and B(x). 

The approach uses the relationship between the coefficients of a polynomial and its 
shifted version through combinatorial identities. Specifically, it utilizes the fact 
that for a polynomial of degree d, if we have values at points 0,1,...,d, we can compute 
certain weighted sums that help determine the shift 's'.

Time Complexity: O(d log d) due to combination calculations and the use of modular arithmetic.
Space Complexity: O(d) for storing factorial and combination tables.

Techniques Used:
- Fast combination calculation using precomputed factorials and modular inverse
- Modular arithmetic for handling large numbers
- Combinatorial identities for polynomial transformation
"""

import sys

input = sys.stdin.readline


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


input = sys.stdin.readline


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


_index, _sep, buffer = 1, False, [""]


def read_int():
    global _index, buffer, _sep
    if _index < len(buffer) - 1 or _sep and _index < len(buffer):
        _index += 1
        return int(buffer[_index - 1])
    else:
        try:
            s = "" if _sep else buffer[-1]
            s += sys.stdin.readline(8192)
            _sep = not s[-1].isdigit()
            buffer = s.split()
        except:
            pass
        _index = 0
    _index += 1
    return int(buffer[_index - 1])


d = II()
mod = 10**9 + 7
fact = Factorial(10**5 * 25, mod)

x1, x2 = 0, 0
for i in range(d + 1):
    val = read_int()
    if i % 2 == 0:
        if i < d:
            x1 += fact.comb(d - 1, i) * val  # Accumulate weighted sum based on parity
        x2 += fact.comb(d, i) * val       # Add contribution to x2
    else:
        if i < d:
            x1 -= fact.comb(d - 1, i) * val  # Subtract from x1 if odd index
        x2 -= fact.comb(d, i) * val       # Subtract from x2 if odd index
    x1 %= mod
    x2 %= mod

y1 = 0
for i in range(d):
    val = read_int()
    if i < d:
        if i % 2 == 0:
            y1 += fact.comb(d - 1, i) * val  # Accumulate weighted sum from B polynomial
        else:
            y1 -= fact.comb(d - 1, i) * val  # Subtract if odd index

diff = (x1 - y1) % mod
print(diff * pow(x2, mod - 2, mod) % mod)  # Compute s using modular inverse


# https://github.com/VaHiX/CodeForces/