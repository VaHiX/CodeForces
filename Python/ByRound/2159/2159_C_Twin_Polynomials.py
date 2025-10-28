# Problem: CF 2159 C - Twin Polynomials
# https://codeforces.com/contest/2159/problem/C

"""
C. Twin Polynomials

This code solves a problem involving "cool" polynomials, which are polynomials equal to their twin polynomial.
The twin polynomial g(x) is defined such that g(x) = sum_{i=0}^n i * x^{a_i}.

Approach:
1. For each test case:
   - Parse input for degree n and coefficients a[], where -1 indicates unknowns
   - Process the known values to enforce constraints from the twin polynomial condition f(x) = g(x)
   - Use dynamic programming to count valid combinations of unknown coefficients

Time Complexity: O(n) per test case, due to linear processing of the array and DP computation
Space Complexity: O(n) for storing the array and DP table

Algorithms/Techniques:
- Twin polynomial definition and constraint checking
- Dynamic Programming for counting valid configurations
"""

import sys

input = sys.stdin.readline
MOD = pow(10, 9) + 7
out = []
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    bad = 0
    for i in list(range(1, n + 1)) * 2: # Loop twice to apply constraints properly
        if a[i] > 0: # If current coefficient is known and positive
            if a[i] > n: # Check bounds of index
                bad = 1
            else:
                if a[a[i]] != -1 and a[a[i]] != i: # If mapping contradicts existing value
                    bad = 1
                a[a[i]] = i # Set inverse mapping (key constraint from twin poly)
    if bad: # If constraint violation found
        out.append(0)
        continue
    v = a[1:].count(-1) # Count remaining unknowns (excluding a[0])
    dp = [1] # DP table initialized with base case
    for i in range(1, v + 1):
        curr = (1 + (i != v or a[n] != -1)) * dp[i - 1] # Current count based on position and final value
        if i >= 2:
            curr += dp[i - 2] * (i - 1) # Add combinations from previous state
        curr %= MOD # Keep modulo to prevent overflow
        dp.append(curr)
    out.append(dp[v])
print("\n".join(map(str, out)))



# https://github.com/VaHiX/CodeForces/