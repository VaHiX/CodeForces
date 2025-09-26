# Problem: CF 2127 F - Hamed and AghaBalaSar
# https://codeforces.com/contest/2127/problem/F

"""
F. Hamed and AghaBalaSar
Algorithm: Combinatorics + Inclusion-Exclusion + Dynamic Programming
Time Complexity: O(MX + n * m) where MX = 400001
Space Complexity: O(MX)

This solution computes the sum of f(a) over all possible "snake" arrays of length n with sum m.
A snake array satisfies:
1. All elements between 0 and m,
2. Sum of elements equals m,
3. Last element is maximum among all.

The function f(a) calculates a value based on a "next greater element" lookup table.
The approach uses combinatorics, inclusion-exclusion principles, and precomputed factorials
and inverse factorials for efficient binomial coefficient computation.
"""

mod = 1000000007
MX = 400001
fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % mod
inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, mod)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % mod


def comb(n: int, k: int) -> int:
    # Compute binomial coefficient C(n, k) mod mod
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod


def g(n, m, l):
    # Computes a sum involving inclusion-exclusion based on constraints
    if n == 0:
        return 1 if m == 0 else 0
    ans = 0
    for t in range(0, min(n, m // (l + 1)) + 1):
        # Use inclusion-exclusion: add if even number of terms, subtract otherwise
        res = comb(n, t) * comb(m + n - 1 - t * (l + 1), n - 1) % mod
        ans = (ans + res) % mod if t % 2 == 0 else (ans - res) % mod
    return ans


from sys import stdin

input = lambda: stdin.readline().rstrip()


def solve():
    n, m = map(int, input().split())
    ans = 0
    inv = pow(n - 1, -1, mod)
    for x in range(0, m + 1):
        g1 = g(n - 1, m - x, x)       # Calculate one part of inclusion-exclusion
        g2 = g(n - 2, m - 2 * x, x)   # Calculate another part of inclusion-exclusion
        res = (g1 * inv + g2) % mod   # Combine using modular inverse and add contribution to result
        ans = (ans + (n * x - m) * res) % mod   # Add weighted sum to final answer
    return ans


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/