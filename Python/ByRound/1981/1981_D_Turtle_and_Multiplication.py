# Problem: CF 1981 D - Turtle and Multiplication
# https://codeforces.com/contest/1981/problem/D

"""
Algorithm: Construct a sequence of integers such that all pairwise products of adjacent elements are unique,
and the number of distinct elements is minimized.

Approach:
1. Precompute primes up to a large limit (11807) using Sieve of Eratosthenes.
2. For each test case:
   - If n < 8, use a hardcoded small sequence.
   - Otherwise, find a suitable r such that we can construct a valid sequence.
   - Generate a sequence using a helper function 'g(r)' that ensures unique products.
   - Map indices to primes and output the result.

Time Complexity: O(m log log m + n) where m is the sieve limit.
Space Complexity: O(m + n) for storing primes and intermediate data.

Techniques:
- Sieve of Eratosthenes for prime generation.
- Modular arithmetic and cycle construction to ensure unique products.
"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())
from math import gcd

m = 11807
# Sieve of Eratosthenes to find all primes up to m
p = [0, 0] + [1] * (m - 1)
for i in range(2, 108):
    if p[i]:
        p[2 * i :: i] = [0] * (m // i - 1)
p = [i for i in range(m + 1) if p[i]]


def g(r):
    # Generate a sequence of length r using modular arithmetic to ensure unique products
    q = set(i for i in range(2, (r + 1) // 2) if r % i == 0)
    e = [[] for _ in range(r)]
    for i in range(2, (r + 1) // 2):
        w = gcd(i, r)
        if w in q:
            for j in range(w):
                e[j] += (i,)
        else:
            e[0] += (i,)
    z = []
    for i in range(r):
        z += (i,)
        for y in e[i]:
            while 1:
                z += ((z[-1] + y) % r,)
                if z[-1] == i:
                    break
        z += (i,)
    z += (0,)
    if not r & 1:
        z += (r // 2,)
    return z


for _ in range(int(R())):
    n = int(R())
    if n < 8:
        # Hardcoded result for small n
        print(*[2, 2, 3, 3, 5, 5, 2][:n])
        continue
    r = 1
    while 1:
        # Adjust r to fit the constraint for the number of elements needed
        if r & 1 and n > r * (r + 1) // 2 + 1:
            r += 1
        elif (r & 1) == 0 and n > r * r // 2 + 2:
            r += 1
        else:
            break
    x = g(r)
    # Map indices to primes and output the final sequence
    print(*[p[x[i]] for i in range(n)])


# https://github.com/VaHiX/CodeForces/