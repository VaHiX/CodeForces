# Problem: CF 2065 G - Skibidus and Capping
# https://codeforces.com/contest/2065/problem/G

"""
Purpose: 
This code solves the problem of counting ordered pairs (i, j) such that i <= j and lcm(a[i], a[j]) is a semi-prime.
A semi-prime is a number that is the product of exactly two prime numbers (not necessarily distinct).
The solution uses precomputed sieve and semi-prime lookup tables to efficiently determine valid pairs.

Algorithms/Techniques:
- Sieve of Eratosthenes for prime number identification
- SPF (Smallest Prime Factor) lookup table for prime factorization
- Classification of numbers as prime or semi-prime
- Counting of valid pairs by frequency of primes and semi-primes

Time Complexity:
- Preprocessing (sieve and semi-prime computation): O(MAX log log MAX)
- Per test case: O(n) where n is the size of the array
- Overall: O(MAX log log MAX + sum of n across all test cases)

Space Complexity:
- O(MAX) for storing sieve, SPF, and semi-prime arrays
"""

import sys
from math import isqrt

MAX = 200000


def compute_sieve_and_spf(limit):
    # Compute sieve of Eratosthenes and smallest prime factor (SPF) for all numbers up to limit
    is_prime = [True] * (limit + 1)
    spf = list(range(limit + 1))
    is_prime[0] = is_prime[1] = False
    for i in range(2, isqrt(limit) + 1):
        if is_prime[i]:
            for j in range(i * i, limit + 1, i):
                if is_prime[j]:
                    is_prime[j] = False
                    spf[j] = i
    return is_prime, spf


def compute_semiprime(limit, is_prime, spf):
    # Identify semi-prime numbers using SPF and prime status
    is_semiprime = [False] * (limit + 1)
    for x in range(2, limit + 1):
        if is_prime[x]:
            continue
        p = spf[x]
        q = x // p
        if p != 0 and is_prime[q] and p * q == x:
            is_semiprime[x] = True
    return is_semiprime


IS_PRIME, SPF = compute_sieve_and_spf(MAX)
IS_SEMIPRIME = compute_semiprime(MAX, IS_PRIME, SPF)


def solve_test_case(n, arr):
    # Count frequencies of numbers that are either prime or semi-prime
    freq = {}
    for x in arr:
        if IS_PRIME[x] or IS_SEMIPRIME[x]:
            freq[x] = freq.get(x, 0) + 1

    # Count pairs (i, j) where both numbers are prime
    total_primes = 0
    sum_sq = 0
    for x, f in freq.items():
        if IS_PRIME[x]:
            total_primes += f
            sum_sq += f * f
    cnt1 = (total_primes * total_primes - sum_sq) // 2

    # Count pairs (i, j) where one is prime and the other is a semi-prime that factors into two primes
    cnt2 = 0
    for a, f_a in freq.items():
        if IS_SEMIPRIME[a]:
            p = SPF[a]
            q = a // p
            add = 0
            if p in freq and IS_PRIME[p]:
                add += freq[p]
            if q != p and q in freq and IS_PRIME[q]:
                add += freq[q]
            cnt2 += f_a * add

    # Count pairs (i, j) where both are semi-prime (i.e., when i == j)
    cnt3 = 0
    for a, f_a in freq.items():
        if IS_SEMIPRIME[a]:
            cnt3 += f_a * (f_a + 1) // 2

    # Return total number of valid pairs
    return cnt1 + cnt2 + cnt3


def main():
    input_line = sys.stdin.readline
    t = int(input_line().strip())
    for _ in range(t):
        n = int(input_line().strip())
        arr = list(map(int, input_line().split()))
        result = solve_test_case(n, arr)
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/