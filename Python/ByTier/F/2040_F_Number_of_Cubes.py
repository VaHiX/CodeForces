# Problem: CF 2040 F - Number of Cubes
# https://codeforces.com/contest/2040/problem/F

"""
Number of Cubes - Burnside's Lemma + Multiplicative Functions
Algorithm: 
- Using Burnside's lemma to count distinct colorings under group actions (cyclic shifts)
- Preprocessing Euler's totient function using sieve of Eratosthenes
- Computing the number of valid assignments using combinatorics

Time Complexity: O(MAX * log(log(MAX)) + k * sqrt(a) * sqrt(b) * sqrt(c))
Space Complexity: O(MAX)

Approach:
- Compute the number of valid colorings using Burnside's lemma
- Each orbit (equivalence class) corresponds to a specific combination of shifts in each direction
- We compute how many elements are fixed by a given shift using the multiplicative property of the Euler totient function
- Use modular arithmetic and combinatorics to determine final count
"""

from math import gcd


def lcm(a, b):
    return a * b // gcd(a, b)


MOD = 0x3B800001 # 998244353 = 2^23 * 7 * 17 + 1

MAX = 3_000_033
fact = [1]
for i in range(1, MAX):
    fact.append(fact[-1] * i % MOD)

# Sieve to compute Euler's totient function (multiplicative function)
primes = []
sieve = [0] * (MAX + 1)
sieve[1] = 1
for i in range(2, MAX + 1):
    if not sieve[i]:
        primes.append(i)
        sieve[i] = i - 1
    for p in primes:
        if i * p > MAX:
            break
        if i % p > 0:
            sieve[i * p] = sieve[i] * sieve[p]
        else:
            sieve[i * p] = sieve[i] * p
            break


def prime_factorization(n):
    pf = []
    for p in primes:
        if n % p == 0:
            e = 0
            while n % p == 0:
                n //= p
                e += 1
            pf.append((p, e))
        if p * p > n:
            break
    if n > 1:
        pf.append((n, 1))
    return pf


def divisors(n):
    divs = [1]
    for p, e in prime_factorization(n):
        L = len(divs)
        for _ in range(L * e):
            divs.append(divs[-L] * p)
    return divs


for _ in range(int(input())):
    a, b, c, k = [int(t) for t in input().split()]
    d = [int(t) for t in input().split()]
    m = {}

    # Precompute totient values for all divisors of a, b, c
    x = {d: sieve[d] for d in divisors(a)}
    y = {d: sieve[d] for d in divisors(b)}
    z = {d: sieve[d] for d in divisors(c)}

    # For every combination of shifts in all three dimensions
    for X in x:
        for Y in y:
            for Z in z:
                L = lcm(lcm(X, Y), Z)  # LCM gives the number of unique positions
                if not L in m:
                    m[L] = 0
                m[L] += x[X] * y[Y] * z[Z]

    S = 0
    for gsize in m:
        P = fact[a * b * c // gsize]  # Number of ways to arrange total cubes
        D = 1
        # Check if distribution is divisible by gsize for each color
        for e in d:
            if not e % gsize == 0:
                P = 0
                break
            D = D * fact[e // gsize] % MOD  # Product of factorials for each color group
        if P:
            S += m[gsize] * P * pow(D, -1, MOD)  # Add contribution for this cycle
            S %= MOD
    S = S * pow(a * b * c, -1, MOD) % MOD  # Normalize by total number of configurations
    print(S)


# https://github.com/VaHiX/CodeForces/