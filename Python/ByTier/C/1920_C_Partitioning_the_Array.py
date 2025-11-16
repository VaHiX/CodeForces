# Problem: CF 1920 C - Partitioning the Array
# https://codeforces.com/contest/1920/problem/C

"""
Algorithm: 
- For each divisor k of n, check if there exists an integer m >= 2 such that all subarrays of length k become identical after taking remainders modulo m.
- This is equivalent to checking if the differences between elements in the same position across subarrays are divisible by some m > 1.
- To optimize, we use factorization and GCD properties to reduce redundant checks.
- Time Complexity: O(n * log(n) + d(n) * n), where d(n) is the number of divisors of n.
- Space Complexity: O(n + log(n)) for sieve and auxiliary data structures.
"""
import math as mt
import sys
from collections import defaultdict
from math import gcd

lol = lambda func=int: list(map(func, sys.stdin.readline().split()))
t = lol()[0]
MAXN = 2 * 10**5 + 1
spf = [i if i & 1 else 2 for i in range(MAXN)]  # Smallest prime factor array


def sieve():
    # Precompute smallest prime factors for all numbers up to MAXN
    for i in range(3, mt.ceil(mt.sqrt(MAXN))):
        if spf[i] == i:
            for j in range(i * i, MAXN, i):
                if spf[j] == j:
                    spf[j] = i


def getFactorization(x):
    # Returns factorization of x as a dictionary of {prime: count}
    ret = defaultdict(lambda: 0)
    while x != 1:
        ret[spf[x]] += 1
        x = x // spf[x]
    return ret


sieve()  # Run sieve once to precompute SPF


def solve(n, a, mn, gg=0):
    # This function recursively computes valid k values for the current subarray
    f = getFactorization(n)
    ans = 1  # At least one point (k = n always works)
    for k in f:
        if k >= mn:  # Only process valid divisors >= mn to avoid redundancy
            q = n // k  # Number of subarrays
            b = a[:q]  # First q elements (representing one full cycle)
            g = gg
            # Compute GCD of differences between elements in same positions
            for i in range(n):
                g = gcd(g, abs(a[i] - b[i % q]))
            if g != 1:  # If GCD > 1, then there's a non-trivial m that satisfies conditions
                # Recursively solve for the reduced array
                ans += solve(q, b, k, g)
    return ans


for _ in range(t):
    n = lol()[0]
    a = lol()
    print(solve(n, a, 0))


# https://github.com/VaHiX/CodeForces/