# Problem: CF 1794 D - Counting Factorizations
# https://codeforces.com/contest/1794/problem/D

"""
Counting Factorizations

Given a list of 2n integers representing the multiset of prime factors and their exponents,
determine how many positive integers m satisfy f(m) = {a1, a2, ..., a2n}.

The approach:
1. For each prime factor p and its exponent e, we need to count how many ways we can assign
   the exponents among the primes in the factorization.
2. We process the list in pairs (p, e) and use dynamic programming to count valid assignments.
3. For each prime, we determine if it's actually a prime number, which is crucial to valid factorizations.
4. Factorial and modular inverse precomputations are used for combinatorial computation.
5. The final result is the multinomial coefficient adjusted for the primes involved.

Time Complexity: O(n * sqrt(max(a_i)) + n^2)
Space Complexity: O(n)

Algorithm:
- Use dynamic programming on the count of exponents.
- Precompute factorials and modular inverses for combinatorics.
- Check if a number is prime to decide whether it's a valid prime in the factorization.

"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())

mod = 998244353

n = int(input())
a = map(int, input().split())

c = {}

for x in a:
    c[x] = c.get(x, 0) + 1

f = [1] * (2 * n + 1)
inv = [1] * (2 * n + 1)

# Precompute factorials and their modular inverses
for i in range(1, 2 * n + 1):
    f[i] = f[i - 1] * i % mod
    inv[i] = pow(f[i], mod - 2, mod)

dp = [0] * (n + 1)
dp[0] = 1
ans = 1

# Process each prime/exponent pair
for pi, ci in c.items():
    prime = pi != 1
    # Check if pi is actually a prime number
    for d in range(2, pi):
        if d * d > pi:
            break
        if pi % d == 0:
            prime = False
            break
    if prime:
        # If pi is prime, update dp using dynamic programming
        for i in range(n, 0, -1):
            dp[i] = (dp[i] + dp[i - 1] * ci) % mod

    # Multiply result by the inverse of factorial of count of this element
    ans = ans * inv[ci]

# Multiply answer by total permutations of exponents and dp[n]
ans = ans * f[n] * dp[n] % mod
print(ans)


# https://github.com/VaHiX/CodeForces/