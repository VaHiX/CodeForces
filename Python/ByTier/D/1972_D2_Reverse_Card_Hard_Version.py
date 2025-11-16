# Problem: CF 1972 D2 - Reverse Card (Hard Version)
# https://codeforces.com/contest/1972/problem/D2

"""
Algorithm: Number Theoretic Approach with GCD Optimization
Technique: 
- The condition b * gcd(a, b) % (a + b) == 0 can be rewritten as:
  b * gcd(a, b) = k * (a + b) for some integer k.
- Let g = gcd(a, b), so a = g * i, b = g * j where gcd(i, j) = 1.
- Substituting: g * j * g = k * (g * i + g * j) => g^2 * j = k * g * (i + j)
  => g * j = k * (i + j)
- Therefore: k = g * j / (i + j), which must be integer. So (i + j) divides g * j.
- We iterate over all coprime pairs (i, j) and count valid (a, b) such that a <= n, b <= m.

Time Complexity: O(√n * √m * log(min(n,m)))
Space Complexity: O(1)

This solution uses an optimized enumeration based on coprime pairs and checks divisibility constraints.
"""

import math


def fun(n, m):
    pairs = 0
    # Iterate through all possible i,j such that gcd(i,j) == 1
    for i in range(1, int((n**0.5) + 1)):
        for j in range(1, int((m**0.5) + 1)):
            if math.gcd(i, j) == 1:
                # For each coprime pair (i, j), we can form multiples (a,b)
                # such that a = i * k and b = j * k for some k
                # The constraint becomes: gcd(a,b) * b = k * (a + b)
                # which simplifies to j * k = k * (i + j), so it holds for any k
                # So counting valid multiples under limits n, m
                pairs += min(n // ((i + j) * i), m // ((i + j) * j))

    return pairs


t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    print(fun(n, m))


# https://github.com/VaHiX/CodeForces/