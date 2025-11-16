# Problem: CF 2048 G - Kevin and Matrices
# https://codeforces.com/contest/2048/problem/G

"""
Algorithm/Techniques: Inclusion-Exclusion Principle, Modular Exponentiation, Combinatorics

Time Complexity: O(n * v * log(mod)) per test case due to modular exponentiation and combinatorics.
Space Complexity: O(max(n, v)) for precomputing factorials and inverse factorials.

This solution uses inclusion-exclusion principle to count matrices satisfying:
min_i(max_j(a[i][j])) <= max_j(min_i(a[i][j]))
by iterating over all possible values of min and max and applying the inclusion-exclusion formula.
"""

import sys
from itertools import accumulate

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)

MOD = 998244353

N = 1000001
# Precompute factorials and inverse factorials for combinations
(*fac,) = accumulate(range(1, N + 1), lambda p, x: p * x % MOD, initial=1)
(*invfac,) = accumulate(
    range(N, 0, -1), lambda p, x: p * x % MOD, initial=pow(fac[-1], -1, MOD)
)
invfac.reverse()


def sum(I):
    t = 0
    for x in I:
        t = (t + x) % MOD
    return t


def pow(b, p, m):
    r = 1
    while p:
        if p & 1:
            r = (r * b) % m
        p >>= 1
        b = (b * b) % m
    return r


def comb(n, k):
    return fac[n] * invfac[k] * invfac[n - k] % MOD


def main():
    n, m, v = map(int, input().split())
    # Iterate over all possible values k of the minimum value in matrix rows
    print(
        sum(
            sum(
                (-1) ** i
                * comb(n, i)
                * (
                    pow(
                        (
                            -pow(v - k + 1, n - i, MOD)
                            + pow(k, i, MOD) * pow(v, n - i, MOD)
                        )
                        % MOD,
                        m,
                        MOD,
                    )
                    - pow((pow(k, i, MOD) * pow(v, n - i, MOD)) % MOD, m, MOD)
                )
                % MOD
                for i in range(1, n + 1)
            )
            for k in range(1, v + 1)
        )
    )


tcs = int(input())
for tc in range(tcs):
    main()


# https://github.com/VaHiX/CodeForces/