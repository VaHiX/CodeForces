# Problem: CF 2122 G - Tree Parking
# https://codeforces.com/contest/2122/problem/G

"""
G. Tree Parking

This code solves a problem involving counting valid pairs of sequences (l, r) for a tree with n vertices and k leaves.
The goal is to compute the sum over all labeled trees of the number of valid (l,r) pairs such that:
- Each l[i] < r[i]
- The concatenation of l,r forms a permutation of 1..2n
- The tree is valid under the parking constraint

Algorithms/Techniques:
- Precomputed factorials and inverse factorials for combinatorial calculations
- Stirling numbers of the second kind via inclusion-exclusion (via function T(n, k))
- Fast exponentiation and modular arithmetic for large computations
- Dynamic rebuilding of tables when needed

Time Complexity: O(n * log n) per test case due to modular exponentiation, and preprocessing up to max n.
Space Complexity: O(n) for storing factorials and inverse factorials.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]
mod = 998244353
table_size = 5 * 10**5
fac = [1] * (table_size + 1)
finv = [1] * (table_size + 1)
for i in range(2, table_size + 1):
    fac[i] = fac[i - 1] * i % mod
finv[table_size] = pow(fac[table_size], mod - 2, mod)
for i in range(table_size - 1, -1, -1):
    finv[i] = finv[i + 1] * (i + 1) % mod


def rebuild(n):
    global table_size, fac, finv
    # Extend the tables to accommodate larger values of n
    fac += [0] * (n - table_size)
    finv += [0] * (n - table_size)
    for i in range(table_size + 1, n + 1):
        fac[i] = fac[i - 1] * i % mod
    finv[n] = pow(fac[n], mod - 2, mod)  # Compute inverse of factorial
    for i in range(n - 1, table_size, -1):
        finv[i] = finv[i + 1] * (i + 1) % mod
    table_size = n


def binom(n, k):
    # Compute combination C(n,k) mod mod using precomputed factorials
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    if n > table_size:
        rebuild(n + 10**4)
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def fpow(x, k):
    # Fast modular exponentiation: compute x^k mod mod
    res = 1
    while k:
        if k & 1:
            res = res * x % mod
        x = x * x % mod
        k >>= 1
    return res


def inv(a):
    # Return modular inverse of a using precomputed values or fast exponentiation
    if a < table_size:
        return fac[a - 1] * finv[a] % mod
    return fpow(a, mod - 2)


def T(n, k):
    # Computes the sum involving Stirling numbers of the second kind via inclusion-exclusion
    res = 0
    sgn = 1
    for j in range(k + 1):
        res += sgn * fpow(k - j, n) * binom(n + 1, j)
        sgn = -sgn
        res %= mod
    return res


def solve():
    N, K = map(int, input().split())
    # Main formula involving factorials and computed terms T(N - 1, K)
    ans = fac[2 * N - 1] * inv(fpow(2, N - 1)) % mod * T(N - 1, K) % mod
    print(ans)
    return 0


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/