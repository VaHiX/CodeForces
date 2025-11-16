# Problem: CF 1916 H2 - Matrix Rank (Hard Version)
# https://codeforces.com/contest/1916/problem/H2

"""
Algorithm: Matrix Rank Counting over Finite Field
Purpose: For a given n x n matrix over the field of integers modulo p, 
         count how many such matrices have rank exactly r for r from 0 to k.

Techniques:
- Use combinatorial formulas for counting matrices of fixed rank over finite fields
- Modular arithmetic with precomputed powers
- Dynamic programming to compute factorials and inverses modulo 998244353
- Gauss's formula for counting matrices of rank r: 
  (p^n - p^(n-1)) * (p^n - p^(n-2)) * ... * (p^n - p^0) * p^(r(n-r))

Time Complexity: O(k)
Space Complexity: O(k)

The code calculates the number of n x n matrices over F_p with rank exactly r,
for each r from 0 to k.
"""

n, p, k = map(int, input().split())
p1 = [1]
m = 998244353
# Precompute p^i mod m for i from 0 to k
for i in range(k):
    p1.append(p1[-1] * p % m)

# Precompute (1/p)^i mod m for i from 0 to k
p0 = [1]
q = pow(p, -1, m)  # Modular inverse of p
for i in range(k):
    p0.append(p0[-1] * q % m)

# Precompute a modified factorial-like sequence for ranks
y = pow(p, n, m)
p2 = [1]
for i in range(1, k + 1):
    if p1[i] == 1:
        p2.append(p2[-1] * i % m)
    else:
        p2.append(p2[-1] * (p1[i] - 1) % m)

# Inverse of p2 to get the final coefficients
p3 = [pow(p2[-1], -1, m)]
for i in range(k, 0, -1):
    if p1[i] == 1:
        p3.append(p3[-1] * i % m)
    else:
        p3.append(p3[-1] * (p1[i] - 1) % m)
p3.reverse()  # Reverse to get correct order

# Iteratively compute final answers
x = 1
ans = []
z = 1
for r in range(k + 1):
    if r > n or x == 0:
        ans.append(0)
        continue
    # Compute the number of matrices with rank r
    ans.append(x * x * p3[r] * z % m)
    x *= y - p1[r]
    x %= m
    z *= p0[r]
    z %= m

print(*ans)


# https://github.com/VaHiX/CodeForces/