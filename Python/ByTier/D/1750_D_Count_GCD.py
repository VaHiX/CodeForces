# Problem: CF 1750 D - Count GCD
# https://codeforces.com/contest/1750/problem/D

"""
Count GCD Problem

Algorithm:
- For each position i, we need b[i] such that gcd(b[0], ..., b[i]) = a[i].
- This implies that b[i] must be a multiple of a[i], and gcd(b[0], ..., b[i-1]) must be divisible by a[i].
- The key idea is to compute for each element a[i], how many valid values b[i] can take based on constraints from previous elements.
- We use inclusion-exclusion principle to count bad values (those not satisfying the GCD conditions).

Time Complexity: O(n * sqrt(m) * 2^k) where k is the number of distinct prime factors of a[i-1]/a[i]
Space Complexity: O(log(a[i-1]/a[i])) for storing prime factors

This approach efficiently computes valid sequences using sieve-like logic combined with inclusion-exclusion over prime factors.
"""

mod = 998244353


def inp():
    return [int(e) for e in input().split()]


for ww in range(1, 1 + int(input())):
    n, m = inp()
    a = inp()
    # Check if the sequence is invalid (i.e., a[i] does not divide a[i+1])
    if any([a[i] % a[i + 1] for i in range(n - 1)]):
        print(0)
        continue
    be = 1
    for i in range(1, n):
        # Compute q = number of multiples of a[i] up to m
        q = m // a[i]
        # Compute d = a[i-1] / a[i] to determine constraints
        d = a[i - 1] // a[i]
        l, k = [], 2
        # Factorize d into prime factors
        while d != 1 and k <= 31622:
            if d % k == 0:
                l += [k]
                while d % k == 0:
                    d //= k
            k += 1
        if d != 1:
            l += [d]
        bad = 0
        # Use inclusion-exclusion to count invalid numbers
        for k in range(1, 2 ** len(l)):
            k = bin(k)[2:][::-1]
            f, c = 1, 0
            for j in range(len(k)):
                if k[j] == "1":
                    f *= l[j]
                    c += 1
            if c % 2:
                bad += q // f
            else:
                bad -= q // f
        # Multiply the number of valid choices for b[i]
        be *= q - bad
        be %= mod
    print(be)


# https://github.com/VaHiX/CodeForces/