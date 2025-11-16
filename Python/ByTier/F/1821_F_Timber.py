# Problem: CF 1821 F - Timber
# https://codeforces.com/contest/1821/problem/F

"""
Code Purpose:
This code solves the problem of counting the number of "unfortunate" alleys with m trees of height k,
where each tree can fall either left or right, and no two trees can occupy the same spot when fallen.
The solution uses dynamic programming with combinatorics to calculate valid configurations.

Algorithms/Techniques:
- Combinatorial mathematics using precomputed factorials and inverse factorials for binomial coefficients
- Inclusion-exclusion principle to count valid arrangements
- Fast exponentiation for modular arithmetic
- Preprocessing of powers of 2 for efficiency

Time Complexity:
O(n) - where n is the number of spots for trees. The dominant factor is the precomputation of factorials and powers of 2.

Space Complexity:
O(n) - for storing precomputed factorial and inverse factorial arrays, and powers of 2 up to 10^6.
"""

mod = 998244353

# Precompute factorials and inverse factorials for combinations
table_size = 4 * 10**5
fac = [1] * (table_size + 1)
finv = [1] * (table_size + 1)

for i in range(2, table_size + 1):
    fac[i] = fac[i - 1] * i % mod
finv[table_size] = pow(fac[table_size], mod - 2, mod)
for i in range(table_size - 1, -1, -1):
    finv[i] = finv[i + 1] * (i + 1) % mod


def binom(n, k):
    # Compute binomial coefficient C(n, k) mod 998244353
    if n < 0 or k < 0:
        return 0
    if k > n:
        return 0
    global table_size, fac, finv
    if n > table_size:
        # Extend the tables if needed
        fac += [0] * (n - table_size)
        finv += [0] * (n - table_size)
        for i in range(table_size + 1, n + 1):
            fac[i] = fac[i - 1] * i % mod
        finv[n] = inv(fac[n])
        for i in range(n - 1, table_size, -1):
            finv[i] = finv[i + 1] * (i + 1) % mod
        table_size = n
    return (fac[n] * finv[k] % mod) * finv[n - k] % mod


def fpow(x, k):
    # Fast exponentiation: compute x^k mod mod
    res = 1
    while k:
        if k & 1:  # If k is odd
            res = res * x % mod
        x = x * x % mod
        k >>= 1  # Divide k by 2
    return res


def inv(a):
    # Compute modular inverse of a mod mod using Fermat's little theorem
    if a < table_size:
        return fac[a - 1] * finv[a] % mod
    return fpow(a, mod - 2)


def modint_to_frac(a):
    # This function is not used in the final computation but provides modular fraction representation
    a %= mod
    if a == 0:
        return "0/1"
    for X in range(1, 10000):
        Y = a * X % mod
        if 0 < Y < 10000:
            return str(Y) + "/" + str(X)
        if mod - 10000 < Y < mod:
            return "-" + str(mod - Y) + "/" + str(X)
    return "inexpressible"


# Read input
n, m, k = map(int, input().split())

# Precompute powers of 2 up to 10^6 for efficiency
pow2 = [1] * (10**6)
for i in range(1, 10**6):
    pow2[i] = pow2[i - 1] * 2 % mod

ans = 0
sgn = 1  # Sign for inclusion-exclusion principle

# Iterate over all possible arrangements using inclusion-exclusion
for i in range(m + 1):
    a = m - i  # Number of trees falling to the left
    b = i      # Number of trees falling to the right
    c = n - (a * (k + 1)) - b * (2 * k + 1)  # Remaining space after placing trees
    if c >= 0:
        # Add contribution to total count using binomial coefficients
        ans += sgn * binom(a + b + c, a) * binom(b + c, b) % mod * pow2[a]
        ans %= mod
    sgn = -sgn  # Alternate sign for inclusion-exclusion

# Output result
print(ans % mod)


# https://github.com/VaHiX/CodeForces/