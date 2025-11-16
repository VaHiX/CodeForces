# Problem: CF 1848 E - Vika and Stone Skipping
# https://codeforces.com/contest/1848/problem/E

"""
Algorithm: Stone Skipping Problem
Purpose: For a given coordinate x, find the maximum number of distinct forces f such that stones 
         thrown with force f touch the water at coordinate x. This is equivalent to finding the 
         number of distinct divisors of x (excluding 1 and 2) which is computed using prime factorization.

Approach:
- Precompute smallest prime factor (SPF) for all numbers up to MAXN using Sieve of Eratosthenes.
- For the initial x, decompose it using SPF to count prime factors and their powers.
- Maintain a mapping of used prime factors and update counts during processing.
- For each multiplication step (x_i), update the result by computing new prime factorization.
- Modular arithmetic is used throughout with modular inverse for division.

Time Complexity: O(MAXN * log(log(MAXN)) + q * sqrt(x)) where q is number of queries
Space Complexity: O(MAXN)
"""

import sys

input = sys.stdin.buffer.readline

MAXN = 1000000

# Precompute smallest prime factor for every number up to MAXN
spf = [-1] * (MAXN + 2)
for i in range(2, MAXN + 1):
    if spf[i] == -1:
        for j in range(i + i, MAXN + 1, i):
            spf[j] = i


def calc(x):
    pfac = {}
    # Factorize x using precomputed SPF
    while spf[x] != -1:
        if pfac.get(spf[x], -1) == -1:
            pfac[spf[x]] = 0
        pfac[spf[x]] += 1
        x //= spf[x]
    if x != 1:
        if pfac.get(x, -1) == -1:
            pfac[x] = 0
        pfac[x] += 1
    res, ret = 1, 1
    for k, v in pfac.items():
        if k == 2:
            continue  # Skip factor 2 as it's handled elsewhere
        if used.get(k, -1) == -1:
            used[k] = 0
            res *= v + 1  # Add one for each distinct prime factor
        else:
            ret *= used[k] + 1  # Multiply by number of existing powers + 1
            res *= used[k] + v + 1 # Multiply by total powers (existing + new) + 1
        used[k] += v  # Update usage count
    return res, ret


x, _, mod = map(int, input().split())
used = {}
ans = 1
c = 0

# Reduce x by removing all factors of 2
while x % 2 == 0:
    x //= 2
# Handle odd prime factors manually for efficiency
for i in range(3, int(x**0.5) + 1, 2):
    if x % i == 0:
        v = 0
        while x % i == 0:
            v += 1
            x //= i
        if used.get(i, -1) == -1:
            used[i] = 0
        used[i] += v
        a = v + 1
        # Count how many times modulo is divisible
        while a % mod == 0:
            c += 1
            a //= mod
        ans *= a  # Accumulate multiplier
if x != 1:
    if used.get(x, -1) == -1:
        used[x] = 0
    used[x] += 1
    ans *= 2  # Handle last prime factor

# Process each multiplication
for xi in map(int, input().split()):
    a, b = calc(xi)
    # Adjust for modular arithmetic
    while a % mod == 0:
        c += 1
        a //= mod
    ans = (ans * a) % mod
    # Divide by modular inverse
    while b % mod == 0:
        c -= 1
        b //= mod
    ans = (ans * pow(b, -1, mod)) % mod
    print(0 if c else ans)


# https://github.com/VaHiX/CodeForces/