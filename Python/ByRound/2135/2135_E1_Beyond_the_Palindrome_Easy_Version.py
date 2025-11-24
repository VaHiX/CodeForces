# Problem: CF 2135 E1 - Beyond the Palindrome (Easy Version)
# https://codeforces.com/contest/2135/problem/E1

"""
E1. Beyond the Palindrome (Easy Version)

Purpose:
This code computes the number of distinct "almost-palindrome" binary strings of length n,
modulo 998244353. An almost-palindrome is defined as a binary string s where f(s) == f(reverse(s)),
where f(r) removes all "10" substrings simultaneously until none remain.

Algorithms/Techniques:
- Preprocessing using sieve-like computation of odd divisors via `sigma_odd_upto`
- Efficient lookup table generation for function g(m) via bit manipulation
- Combinatorial counting with modular arithmetic and precomputed factorials/inverse factorials
- Dynamic programming-style summation over combinations

Time Complexity:
O(N log N + T * N), where N = max(n in input), T = number of test cases.
Space Complexity:
O(N), for storing lookup tables and auxiliary arrays.

"""

import sys

MOD = 998244353


def sigma_odd_upto(N):
    # Computes sum of odd divisors for each number up to N
    s = [0] * (N + 1)
    for d in range(1, N + 1, 2):  # Only iterate over odd numbers
        step = d << 1  # Equivalent to 2*d
        for m in range(d, N + 1, step):
            s[m] += d  # Add divisor d to all multiples of d
    return s


def build_g(N_plus_1):
    # Precompute g(m) values based on sigma_odd_upto and bit decomposition
    sig = sigma_odd_upto(N_plus_1)
    g = [0] * (N_plus_1 + 1)
    for m in range(1, N_plus_1 + 1):
        p2 = m & -m  # Isolate the largest power of 2 dividing m
        odd = m // p2  # Extract the odd part of m
        g[m] = (p2 * sig[odd]) % MOD  # Use precomputed odd divisor sum
    return g


def build_fact_ifact(N):
    # Precompute factorials and inverse factorials modulo MOD
    fact = [1] * (N + 1)
    ifact = [1] * (N + 1)
    for i in range(1, N + 1):
        fact[i] = fact[i - 1] * i % MOD
    ifact[N] = pow(fact[N], MOD - 2, MOD)  # Modular inverse via Fermat's little theorem
    for i in range(N, 0, -1):
        ifact[i - 1] = ifact[i] * i % MOD  # Compute inverse factorials bottom-up
    return fact, ifact


def main():
    data = list(map(int, sys.stdin.read().split()))
    t, ns = data[0], data[1:]
    N = max(ns)
    g = build_g(N + 1)
    fact, ifact = build_fact_ifact(N)
    out = []
    for n in ns:
        fn = fact[n]  # Factorial of n
        total = 0
        for i in range(n + 1):
            comb = fn * ifact[i] % MOD * ifact[n - i] % MOD  # Binomial coefficient C(n, i)
            a = n - 2 * i - 1
            if a < 0:
                a = -a
            b = n - 2 * i
            if b < 0:
                b = -b
            total = (total + comb * ((g[a] - g[b]) % MOD)) % MOD
        ans = (2 * total) % MOD  # Apply doubling factor from the formula
        pow2 = pow(2, n, MOD)
        if ((n + 1) & 1) == 0:  # If (n+1) is even
            ans = (ans + pow2) % MOD  # Add 2^n to result
        else:
            ans = (ans - pow2) % MOD  # Subtract 2^n from result
        out.append(str(ans % MOD))
    print("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/