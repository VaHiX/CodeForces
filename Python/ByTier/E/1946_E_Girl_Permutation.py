# Problem: CF 1946 E - Girl Permutation
# https://codeforces.com/contest/1946/problem/E

"""
Problem: Girl Permutation
Algorithm: Combinatorics and Dynamic Programming
Time Complexity: O(n) per test case
Space Complexity: O(n)

This solution computes the number of permutations of length n given the indices
of prefix maximums and suffix maximums. It uses combinatorics to count valid arrangements,
ensuring that constraints from prefix and suffix maxima are satisfied.

The key idea is to determine how many ways we can place numbers in segments 
defined by maxima positions and use combinations to calculate valid arrangements.
"""

import sys

input = lambda: sys.stdin.readline().strip()
mod = 10**9 + 7
n = 300000
fact = [1 for i in range(n + 1)]
fact_inv = [1 for i in range(n + 1)]
for i in range(1, n + 1):
    fact[i] = fact[i - 1] * i % mod
fact_inv[-1] = pow(fact[-1], mod - 2, mod)
for i in range(n, 0, -1):
    fact_inv[i - 1] = fact_inv[i] * i % mod


def comb(n, r):
    # Compute combination C(n, r) = n! / (r! * (n - r)!)
    if r > n:
        return 0
    if n < 0:
        return 0
    if r < 0:
        return 0
    res = fact_inv[n - r] * fact_inv[r] % mod
    res *= fact[n]
    res %= mod
    return res


def f(n, r):
    # Compute falling factorial F(n, r) = n * (n - 1) * ... * (n - r + 1)
    if r > n:
        return 0
    if n < 0:
        return 0
    if r < 0:
        return 0
    res = fact_inv[n - r] * fact[n]
    res %= mod
    return res


t = int(input())
for _ in range(t):
    n, m, mm = map(int, input().split())
    p = list(map(int, input().split()))
    s = list(map(int, input().split()))
    
    # Check if the problem constraints are satisfied (first prefix max is 1, last suffix max is n, and they match)
    if p[-1] != s[0]:
        print(0)
        continue
    if p[0] != 1:
        print(0)
        continue
    if s[-1] != n:
        print(0)
        continue

    # First segment: before the first suffix max
    ans = comb(n - 1, s[0] - 1)
    l = s[0] - 1
    L = []
    
    # Calculate gaps between consecutive prefix maxima
    for i in range(m - 1, 0, -1):
        x = p[i] - p[i - 1] - 1
        L.append(x)
    
    # Process left gaps in reverse order to maintain correct combinatorial calculation
    for x in L:
        l -= 1
        ans *= f(l, x)
        ans %= mod
        l -= x
    
    # Right segment: after the last prefix max
    r = n - s[0]
    R = []
    
    # Calculate gaps between consecutive suffix maxima
    for i in range(mm - 1):
        x = s[i + 1] - s[i] - 1
        R.append(x)
    
    # Process right gaps in order
    for x in R:
        r -= 1
        ans *= f(r, x)
        ans %= mod
        r -= x
    
    print(ans)


# https://github.com/VaHiX/CodeForces/