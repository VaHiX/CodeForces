# Problem: CF 2060 F - Multiplicative Arrays
# https://codeforces.com/contest/2060/problem/F

"""
F. Multiplicative Arrays

Algorithms/Techniques:
- Preprocessing using dynamic programming to count multiplicative arrays of length up to rmax.
- Combinatorial number calculation for binomial coefficients.
- Modular arithmetic and modular inverse for computations under modulo 998244353.
- Fast exponentiation for modular inverse.

Time Complexity: O(k * rmax + k * log(k) + t * k * rmax)
Space Complexity: O(k + rmax + k * rmax)

The solution builds a DP table where ways[r][x] is the number of arrays of length r with product x.
Then, for each query (k, n), it computes how many such arrays exist for each x from 1 to k,
by combining the precomputed DP values with binomial coefficients.

Input Format:
- Number of test cases t
- For each case: k and n

Output Format:
- For each case: k space-separated integers representing answer for x = 1 to k.
"""

from functools import lru_cache

mod = 998244353
kmax = 100000
rmax = 16
ways = [[0] * (kmax + 1) for _ in range(rmax + 1)]


@lru_cache(None)
def mod_inv(a, p=mod):
    # Compute modular inverse using fast exponentiation
    res, base = 1, a % p
    exp = p - 2
    while exp > 0:
        if exp & 1:
            res = (res * base) % p
        base = (base * base) % p
        exp >>= 1
    return res


def comb(n, r):
    # Calculate combination C(n, r) modulo mod
    if r > n:
        return 0
    ans = 1 % mod
    nmod = n % mod
    for i in range(r):
        term = ((nmod - i) % mod + mod) % mod
        ans = (ans * term) % mod
        ans = (ans * invs[i + 1]) % mod
    return ans


# Precompute modular inverses up to 17
invs = [0] * 18
for i in range(1, 18):
    invs[i] = mod_inv(i)

# Initialize base case: arrays of length 1 have product equal to their element value
for x in range(2, kmax + 1):
    ways[1][x] = 1

# Dynamic Programming step: fill ways[r][x] for all lengths r from 2 to rmax
for r in range(2, rmax + 1):
    for x in range(1, kmax + 1):
        w = ways[r - 1][x]
        if w != 0:
            # For each multiple of x, update the count of arrays with that product
            for muls in range(2 * x, kmax + 1, x):
                ways[r][muls] = (ways[r][muls] + w) % mod

# Process test cases
for _ in range(int(input())):
    k, n = map(int, input().split())
    
    # Precompute binomial coefficients for current n
    binval = [0] * (rmax + 1)
    for r in range(1, rmax + 1):
        if r <= n:
            binval[r] = comb(n + 1, r + 1)
        else:
            binval[r] = 0
    
    # ans[x] will store result for product x
    ans = [0] * (k + 1)
    ans[1] = n % mod  # Base case: for product 1
    
    # Compute for all products from 2 to k
    for x in range(2, k + 1):
        sumx = 0
        for r in range(1, rmax + 1):
            if binval[r] == 0:
                break  # Early termination when coefficients become zero
            w = ways[r][x]
            if w != 0:
                tmp = (w * binval[r]) % mod
                sumx = (sumx + tmp) % mod
        ans[x] = sumx
    
    print(" ".join(map(str, ans[1:])))


# https://github.com/VaHiX/codeForces/