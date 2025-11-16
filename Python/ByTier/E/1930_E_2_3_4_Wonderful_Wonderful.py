# Problem: CF 1930 E - 2..3...4.... Wonderful! Wonderful!
# https://codeforces.com/contest/1930/problem/E

"""
Code Purpose:
This code solves the problem of counting the number of possible arrays that can be obtained
by repeatedly applying a specific operation on an initial array of integers from 1 to n.
The operation involves selecting a subsequence of length 2*k+1 and deleting the first k and last k elements.
The solution uses combinatorics to calculate the number of possible arrangements for each valid value of k.

Algorithms/Techniques:
- Modular arithmetic and combinatorics (nCr calculations using precomputed factorials and modular inverses)
- Inclusion-exclusion principle to count valid subsequences
- Dynamic programming with modular arithmetic

Time Complexity: O(N^2) per test case due to computation of combinations and nested loops
Space Complexity: O(N) for storing precomputed factorials, modular inverses, and combinations
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def cmb(n, r, mod):
    # Calculate combination C(n, r) modulo mod using precomputed factorials
    if r < 0 or r > n:
        return 0
    return (g1[n] * g2[r] % mod) * g2[n - r] % mod


mod = 998244353
N = 2 * 10**6
g1 = [1] * (N + 1)
g2 = [1] * (N + 1)
inverse = [1] * (N + 1)

# Precompute factorials and modular inverses
for i in range(2, N + 1):
    g1[i] = (g1[i - 1] * i) % mod
    inverse[i] = (-inverse[mod % i] * (mod // i)) % mod
    g2[i] = (g2[i - 1] * inverse[i]) % mod
inverse[0] = 0


def solve(N, K):
    # Calculate number of possible arrays for a given k
    res = 0
    # First loop: add all combinations of selecting 2*K*i elements from N total
    for i in range(N // (2 * K) + 1):
        res += cmb(N, 2 * K * i, mod)
        res %= mod

    # Second loop: subtract invalid combinations using inclusion-exclusion principle
    for i in range(1, N // (2 * K) + 1):
        rest = N - 2 * K * i
        # Subtract combinations for remaining elements with constraints
        res -= cmb(rest + 2 * K - 1, 2 * K - 1, mod)
        res %= mod
    return res


for _ in range(int(input())):
    N = int(input())
    # For each k from 1 to floor((n-1)/2), compute the result
    print(*[solve(N, K) for K in range(1, (N - 1) // 2 + 1)])


# https://github.com/VaHiX/CodeForces/