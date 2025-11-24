# Problem: CF 2147 G - Modular Tetration
# https://codeforces.com/contest/2147/problem/G

"""
Problem: Modular Tetration Density Calculation

Algorithms:
- Sieve of Eratosthenes for factorization
- Euler's totient function computation
- Modular exponentiation
- Recursive formula for tetration density
- Prime factorization via sieve
- Efficient modular arithmetic and inversion

Time Complexity: O(n log log n + k * log(k)) where n is the maximum number (10^6) and k depends on number of primes.
Space Complexity: O(n) for the sieve array.

This code computes the density of m-tetrative integers, where m = x*y*z. It uses the concept of modular tetration to determine
which values a have stable sequences mod m.
"""

sieve = [1] * (10**6 + 1)
for i in range(2, 10**6 + 1):
    if sieve[i] == 1:
        for j in range(i, 10**6 + 1, i):
            sieve[j] = i  # Mark smallest prime factor of j


def f(x, y, z):
    """Factorize x*y*z into primes and return their exponents."""
    d = {}
    for i in [x, y, z]:
        while i > 1:
            p = sieve[i]
            if not p in d:
                d[p] = 0
            d[p] += 1
            i //= p
    return d


def f1(i):
    """Factorize a single integer into primes and return their exponents."""
    d = {}
    while i > 1:
        p = sieve[i]
        if not p in d:
            d[p] = 0
        d[p] += 1
        i //= p
    return d


def mult(d1, d2):
    """Multiply two prime exponent dictionaries."""
    for i in d2:
        if not i in d1:
            d1[i] = 0
        d1[i] += d2[i]
    return d1


def phi(d):
    """
    Compute the set of unique primes from factorization dictionary.
    This function returns a set of distinct prime factors.
    """
    ans = set()
    for p in d:
        # Add p to the result set
        for i in f1(p - 1):  # Factorize (p - 1) to find its primes
            ans.add(i)
    return ans


def t(n, d):
    """Recursive function not directly used but defined for compatibility."""
    p = phi(d)
    return pow(n, t(n, p) + p, d)


def g(d):
    """
    Convert a prime exponent dictionary back to an integer.
    That is compute product of primes raised to their powers.
    """
    z = 1
    for i in d:
        z *= i ** d[i]
    return z


def reduce(d, y):
    """Select only those exponents whose base primes are in set y."""
    ans = 1
    for i in d:
        if i in y:
            ans *= i ** d[i]
    return ans


MOD = 998244353
for _ in range(int(input())):
    x, y, z = map(int, input().split())
    d = f(x, y, z)  # Get prime factorization of m = x*y*z
    p = phi(d)      # Compute the set of primes from phi(m), needed for the formula

    # Remove primes that appear in d from p to get unique set
    for i in d:
        if i in p:
            p.remove(i)
    
    n = len(p)  # Number of unique primes
    l = list(p)  # Convert set to list

    ans = 0
    prod = 1
    # Multiply all the primes together, modulo MOD
    for i in range(n):
        prod *= l[i]
        prod %= MOD

    # Add contributions from each prime power to product
    for q in d:
        prod *= q ** d[q]
        prod %= MOD

    z = {}
    for i in l:
        z[i] = 0
    # Accumulate exponents of primes needed for computation
    for q in d:
        z = mult(z, f1(q - 1))  # Factorize (q-1) to extract its prime exponents

    ans = 1
    # Final calculation using the formula based on Euler's theorem and properties of tetration
    for i in range(n):
        # Compute term: (l[i] ** z[l[i]] + l[i] - 1)
        ans *= l[i] ** z[l[i]] + l[i] - 1
    
    # Modular inverse of prod and final modular multiplication
    print(ans * pow(prod, -1, MOD) % MOD)


# https://github.com/VaHiX/CodeForces/