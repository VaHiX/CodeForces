# Problem: CF 1967 B2 - Reverse Card (Hard Version)
# https://codeforces.com/contest/1967/problem/B2

"""
Algorithm: Number Theoretic Approach with GCD Optimization

The problem requires counting ordered pairs (a,b) such that:
1. 1 ≤ a ≤ n, 1 ≤ b ≤ m
2. b * gcd(a, b) is divisible by (a + b)

Key Observations:
- Let g = gcd(a, b). Then a = g * a', b = g * b' where gcd(a', b') = 1.
- The condition becomes (g * b') * g = g^2 * b' is divisible by (g * a' + g * b') = g * (a' + b')
- Simplifying: g^2 * b' is divisible by g * (a' + b') => g * b' is divisible by (a' + b')
- Since gcd(a', b') = 1 and a' + b' > 0, we can derive that (a' + b') divides g * b'
- This leads to considering all divisors s = a + b, and iterating over possible values of a and b such that a + b = s
- For each such s, we count valid pairs (a, b) by fixing a and checking if the constraint holds

Approach:
- Iterate over all possible sums s from 2 to min(N, M)
- For each s, iterate over valid values of a in range [1, s-1], ensuring that we have valid b = s - a
- Since gcd(a, b) = gcd(a, s - a), if gcd(a, s) > 1, it means a and b are not coprime and invalid
- When gcd(a, s) = 1, we count number of valid b values using arithmetic progression bounds

Time Complexity: O(N * log(N)) due to iteration over N and potential gcd computations, but optimized with bounded loop structure
Space Complexity: O(1) - only using a constant amount of extra space
"""

import sys
from math import gcd

input = sys.stdin.readline
F = lambda: [*map(int, input().split())]

for _ in range(int(input())):
    N, M = F()
    ans = 0
    # Iterate over all possible sums s = a + b
    for s in range(2, min(N, M) + 1):
        # Compute maximum value of a such that a < s and a * s <= N
        amax = min(s - 1, N // s)
        # Compute maximum value of b such that b < s and b * s <= M
        bmax = min(s - 1, M // s)
        # If there's no valid a or b, break early
        if amax + bmax < s:
            break
        # Iterate over valid a values
        for a in range(s - bmax, amax + 1):
            # Ensure that gcd(a, s) = 1, indicating that a and s are coprime
            if gcd(a, s) > 1:
                continue
            # Count how many valid values of b exist based on current a and s
            ans += min(N // (a * s), M // ((s - a) * s))

    print(ans)


# https://github.com/VaHiX/CodeForces/