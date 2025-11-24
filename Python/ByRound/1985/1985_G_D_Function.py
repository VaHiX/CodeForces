# Problem: CF 1985 G - D-Function
# https://codeforces.com/contest/1985/problem/G

"""
Purpose: 
    This code solves the problem of counting integers n in the range [10^l, 10^r) such that 
    D(k * n) = k * D(n), where D(n) is the sum of digits of n.

    The key insight is that this condition holds if and only if the digits of n are 
    such that multiplying by k does not cause any carry-over in the digit sum calculation. 
    This happens when all digits of n are less than or equal to 9//k.

    The solution uses a mathematical formula based on geometric progression:
    - For a number with d digits, the number of valid combinations is (p + 1)^d, 
      where p = 9 // k.
    - The result is computed as (pow(p + 1, r, MOD) - pow(p + 1, l, MOD)) % MOD.

Algorithms/Techniques:
    - Mathematical Observation: D(k * n) = k * D(n) is satisfied when digits of n are ≤ 9//k.
    - Modular Exponentiation: Efficient computation of powers modulo 10^9 + 7.
    - Inclusion-Exclusion Principle: Subtracting the count for range [10^l, 10^r).

Time Complexity: O(t * log(r)) due to modular exponentiation per test case.
Space Complexity: O(1) - only a few variables are used.
"""

import sys

input = sys.stdin.readline

t = int(input())
out = []

for _ in range(t):

    l, r, k = map(int, input().split())

    p = 9 // k  # Maximum allowed digit to prevent carry when multiplied by k

    MOD = 10**9 + 7

    # Compute (p + 1)^r - (p + 1)^l mod MOD
    ans = (pow(p + 1, r, MOD) - pow(p + 1, l, MOD) + MOD) % MOD

    out.append(ans)


print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/