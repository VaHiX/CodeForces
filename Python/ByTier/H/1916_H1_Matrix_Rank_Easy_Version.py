# Problem: CF 1916 H1 - Matrix Rank (Easy Version)
# https://codeforces.com/contest/1916/problem/H1

"""
Matrix Rank Counting on Finite Field

This code computes the number of n×n matrices over the finite field F_p (integers modulo p) 
with rank exactly r, for r from 0 to k. 

The approach uses the principle that the number of matrices of rank r is:
    (Number of ways to choose r linearly independent rows) × (Number of ways to complete the matrix)

The formula used is based on the product of Gaussian binomial coefficients (Gaussiants) and is:
    N_r = (p^n - p^0) × (p^n - p^1) × ... × (p^n - p^(r-1)) / (p^r - p^0) × ... × (p^r - p^(r-1))

This can be computed efficiently by precomputing powers of p and using modular inversion.

Time Complexity: O(k)
Space Complexity: O(k)

Algorithm:
1. Precompute powers of p modulo M (M = 998244353)
2. Iterate from 0 to k and calculate the count of matrices with rank r
3. For each r, use the formula involving products of terms (p^n - p^i) and (p^r - p^j)
4. Modular arithmetic with inversion used for division

Implementation Details:
- The variable 'm' holds p^n (mod M)
- Loop computes terms using previously calculated values
- Modular inverse is computed using pow(base, -1, mod)
"""

M = 998244353
P = pow
n, p, k = map(int, input().split())
a = [1]
m = P(p, n, M)
i = 1
R = 1
g = 1
for r in range(k):
    i = (i * (m - R)) % M
    R = (R * p) % M
    g = (g * P(p, r, M) * (R - 1)) % M
    a.append((i * i * P(g, -1, M)) % M if g else 0)
print(" ".join(map(str, a)))


# https://github.com/VaHiX/CodeForces/