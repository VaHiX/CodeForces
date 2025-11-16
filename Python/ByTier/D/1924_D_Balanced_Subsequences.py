# Problem: CF 1924 D - Balanced Subsequences
# https://codeforces.com/contest/1924/problem/D

"""
Algorithm: Dynamic Programming with Combinatorics
Purpose: Count the number of bracket sequences of n '(' and m ')' such that the longest balanced subsequence has length 2*k.

This problem uses the concept of Catalan numbers and combinatorics:
- We calculate the number of valid bracket sequences with length up to 2*k.
- The difference between this and the count with length up to 2*(k-1) gives us the answer.

Time Complexity: O(N) where N = 4005 (precomputation of factorials and inverse factorials)
Space Complexity: O(N) for storing precomputed factorials and inverse factorials

Techniques:
- Modular exponentiation for inverse computation
- Combination formula using precomputed factorials
- Subtraction of counts to isolate the desired range
"""

def power(a, b, p):
    if a == 0:
        return 0
    res = 1
    a %= p
    while b > 0:
        if b & 1:
            res = (res * a) % p
        b >>= 1
        a = (a * a) % p
    return res


def pre():
    global fact, inv
    fact = [0] * N
    inv = [0] * N
    fact[0] = inv[0] = 1
    for i in range(1, N):
        fact[i] = (fact[i - 1] * i) % mod
    for i in range(1, N):
        inv[i] = power(fact[i], mod - 2, mod)


def nCr(n, r):
    if min(n, r) < 0 or r > n:
        return 0
    if n == r:
        return 1
    return (((fact[n] * inv[r]) % mod) * inv[n - r]) % mod


def f(n, m, k):
    if k >= min(n, m):
        # If k is larger than the minimum of n and m, we can form any valid sequence
        return nCr(n + m, m)
    # Otherwise, compute combinations up to k
    return nCr(n + m, k)


N = 4005
mod = 1000000007
pre()
t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    # Subtract to isolate the count of sequences with longest balanced subsequence of exactly 2*k
    result = (f(n, m, k) - f(n, m, k - 1) + mod) % mod
    print(result)


# https://github.com/VaHiX/CodeForces/