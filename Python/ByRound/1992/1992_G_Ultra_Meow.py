# Problem: CF 1992 G - Ultra-Meow
# https://codeforces.com/contest/1992/problem/G

"""
Code Purpose:
This code computes the MEOW(a) value for an array a of length n, where a consists of numbers from 1 to n.
MEOW(a) is defined as the sum of MEX(b, |b|+1) over all distinct subsets b of the array a.
MEX(S, k) is the k-th smallest positive integer not present in set S.

The solution uses combinatorial mathematics and inclusion-exclusion principles:
- Precompute factorials and their modular inverses for combinations C(n, k)
- For each subset size k, calculate contributions to MEOW(a) using:
  - The number of subsets of size k
  - The MEX value for various configurations

Time Complexity: O(N^2) preprocessing, O(N^2) per query
Space Complexity: O(N) for storing factorials and inverses

Algorithms/Techniques:
- Modular arithmetic
- Precomputed factorials and inverse factorials for combination calculations
- Dynamic programming concepts in subset enumeration
- Fast exponentiation for modular inverse

"""

N = 15000
mod = 1000000007
f = [0] * N
r = [0] * N


def mul(a, b):
    return (a * b) % mod


def add(a, b):
    return (a + b) % mod


def sub(a, b):
    return (a - b + mod) % mod


def binpow(a, pw):
    b = 1
    while pw:
        if pw & 1:
            b = mul(b, a)
        a = mul(a, a)
        pw >>= 1
    return b


def inv(a):
    return binpow(a, mod - 2)


def C(n, k):
    if n < 0 or k < 0 or n < k:
        return 0
    return mul(f[n], mul(r[k], r[n - k]))


def precalc():
    f[0] = 1

    for i in range(1, N):
        f[i] = mul(f[i - 1], i)

    r[N - 1] = inv(f[N - 1])
    for i in range(N - 2, -1, -1):
        r[i] = mul(r[i + 1], i + 1)


def solve():
    n = int(input())
    ans = 1
    for k in range(1, n + 1):
        if 2 * k >= n:
            ans = add(ans, mul(2 * k + 1, C(n, k)))
            continue
        for m in range(k + 1, 2 * k + 2):
            c = mul(C(m - 1, m - 1 - k), C(n - m, 2 * k + 1 - m))
            ans = add(ans, mul(c, m))
    print(ans)


T = int(input())
precalc()
for i in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/