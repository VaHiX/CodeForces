# Problem: CF 2039 D - Shohag Loves GCD
# https://codeforces.com/contest/2039/problem/D

"""
D. Shohag Loves GCD

Purpose:
This code solves the problem of constructing a lexicographically largest array of length n such that:
1. Each element belongs to a given set S of m unique integers.
2. For all pairs (i, j) with i < j, gcd(i, j) != gcd(a[i], a[j]).

Algorithm:
- The key insight is to assign elements based on the number of distinct prime factors of indices.
- Uses sieve of Eratosthenes to precompute smallest prime factor for each number.
- Then uses dynamic programming to calculate number of distinct prime factors (ct array).
- For each index, map it to an element in S based on its prime factor count.
- If 2^m <= n, then it's impossible due to pigeonhole principle.

Time Complexity: O(N log N + T * N)
Space Complexity: O(N)

"""

import sys

input = sys.stdin.readline
MX = 10**5 + 10
sieve = [0] * MX
ct = [0] * 2  # ct[i] stores number of distinct prime factors of i

# Sieve of Eratosthenes to compute smallest prime factor (SPF) for each number
for i in range(2, MX):
    if sieve[i]:
        continue
    for j in range(i, MX, i):
        sieve[j] = i  # Mark smallest prime factor of j

# Precompute number of distinct prime factors for all numbers
for i in range(2, MX):
    ct.append(ct[i // sieve[i]] + 1)

out = []
t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    s = list(map(int, input().split()))
    
    # If 2^m <= n, not enough distinct assignments possible
    if (1 << m) <= n:
        out.append("-1")
        continue
    
    res = []
    for i in range(1, n + 1):
        # Map index i to value from set S based on number of prime factors
        res.append(s[~ct[i]])  # ~ct[i] = -ct[i] - 1 used here to get valid index in reverse order
    out.append(" ".join(map(str, res)))

print("\n".join(map(str, out)))


# https://github.com/VaHiX/codeForces/