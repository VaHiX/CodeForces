# Problem: CF 2090 D - Simple Permutation
# https://codeforces.com/contest/2090/problem/D

"""
D. Simple Permutation

Purpose:
This code constructs a permutation of integers from 1 to n such that among the ceiling averages c_i,
there are at least floor(n/3) - 1 prime numbers.

Algorithm:
- Precompute primes up to 100000 using Sieve of Eratosthenes.
- For a given n, find the largest prime number less than or equal to 2*n//3.
- Construct the result list by:
  1. Starting with that prime
  2. Expanding outwards from the prime (left and right)
  3. Adding remaining numbers in order

Time Complexity: O(n * log(log(n))) for sieve + O(n) for construction = O(n * log(log(n)))
Space Complexity: O(n) for storing sieve and result list.

"""

import math

limit = 100000


def soe(limit):
    # Sieve of Eratosthenes to find all primes up to limit
    prime = [True] * (limit + 1)
    prime[0] = prime[1] = False
    for i in range(2, int(math.sqrt(limit)) + 1):
        if prime[i]:
            for j in range(i * i, limit + 1, i):  # Mark multiples of prime as not prime
                prime[j] = False
    return prime


def solve(n, prime):
    res = []
    p = 1
    # Find the largest prime <= 2*n//3
    for i in range(1, 2 * n // 3 + 1):
        if prime[i]:
            p = i
    l, r = p - 1, p + 1
    res.append(p)
    while True:
        if r > n:
            break
        res.append(r)
        r += 1
        if l < 1:
            break
        res.append(l)
        l -= 1
    # Add remaining numbers in order
    res.extend(range(1, l + 1))
    res.extend(range(r, n + 1))
    print(" ".join(map(str, res)))


t = int(input())
prime = soe(limit)
for _ in range(t):
    n = int(input())
    solve(n, prime)


# https://github.com/VaHiX/codeForces/