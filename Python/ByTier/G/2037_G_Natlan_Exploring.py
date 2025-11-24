# Problem: CF 2037 G - Natlan Exploring
# https://codeforces.com/contest/2037/problem/G

"""
Algorithm: Dynamic Programming with Prime Factorization and Möbius Inversion-like Technique
Time Complexity: O(n * sqrt(MAX_A) + MAX_A * log log MAX_A)
Space Complexity: O(MAX_A)

This solution uses a technique similar to Möbius inversion to track the number of paths 
to each city by considering shared prime factors. For each city, we compute its prime 
factorization and update a global counter array (V) that tracks how many paths lead to 
each possible factor (positive or negative). The key idea is to use inclusion-exclusion 
principle through alternating signs during updates, and process cities in order to build 
the number of valid paths from city 1 to city n.

The sieve is used to precompute smallest prime factors for numbers up to MAX_P for efficient factorization.
"""

n = int(input())
a = [int(t) for t in input().split()]
MAX_P = 1_000_000
primes = []
sieve = [0] * (MAX_P + 1)
for i in range(2, MAX_P + 1):
    if not sieve[i]:
        primes.append(i)
    for p in primes:
        if i * p > MAX_P:
            break
        sieve[i * p] = p
        if not i % p:
            break


def rad(k):
    r = []
    while k > 1:
        if 0 == sieve[k]:
            r.append(k)
            break
        p = sieve[k]
        r.append(p)
        while k % p == 0:
            k //= p
    divs = [1]
    for p in r:
        L = len(divs)
        for _ in range(L):
            divs.append(divs[-L] * (-p))
    return divs


V = [0] * 1_000_001
for d in rad(a[0]):
    V[abs(d)] = 1
for i in range(1, n):
    divs = rad(a[i])
    ways = 0
    for d in divs:
        if d == 1:
            continue
        if d > 0:
            ways -= V[d]
        if d < 0:
            ways += V[-d]
    ways %= 0x3B800001
    if i == n - 1:
        print(ways)
    for d in divs:
        V[abs(d)] += ways


# https://github.com/VaHiX/CodeForces/