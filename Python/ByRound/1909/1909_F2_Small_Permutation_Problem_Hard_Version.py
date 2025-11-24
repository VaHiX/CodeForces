# Problem: CF 1909 F2 - Small Permutation Problem (Hard Version)
# https://codeforces.com/contest/1909/problem/F2

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^2) per test case in worst case, but optimized with precomputed factorials and inverse factorials
Space Complexity: O(n) for storing factorials and inverse factorials, and for input arrays

This problem involves counting permutations of [1..n] that satisfy certain constraints specified by array 'a'.
Each element a[i] defines how many numbers <= i should appear in the prefix p[1..i].
We use combinatorics and dynamic programming to compute valid placements.
Precomputed factorials and inverse factorials help with efficient combination calculations.
"""

import sys

input = sys.stdin.buffer.readline
MOD = 998244353
MAXN = 2 * 10**5 + 1
fac = [1] * MAXN
ifac = [1] * MAXN
for i in range(2, MAXN):
    fac[i] = fac[i - 1] * i % MOD
ifac[-1] = pow(fac[-1], -1, MOD)
for i in range(MAXN - 2, -1, -1):
    ifac[i] = ifac[i + 1] * (i + 1) % MOD


def choose(n, k):
    # Calculate combination C(n,k) mod MOD
    if k > n:
        return 0
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD


def ways_mat(a, b, c):
    # Helper function to compute a product of combinations
    ans = choose(a, c) * choose(b, c) * fac[c]
    return ans


for _ in range(int(input())):
    n = int(input())
    a = [0] + list(map(int, input().split()))  # Add dummy 0 at beginning for 1-based indexing
    if a[-1] == -1:
        a[-1] = n  # If last element is -1, set it to n to simplify logic
    bad = False
    imp_a = [x for x in a if x != -1]  # Get all non -1 values
    if a[-1] != n:
        bad = True  # If last required count is not n, invalid
    for i in range(len(imp_a) - 1):
        if imp_a[i] > imp_a[i + 1]:
            bad = True  # If counts are decreasing, not allowed
    if bad:
        ans = 0  # Early return if invalid
    else:
        ans = 1  # Start with one way
        pi = 0  # Previous index where we had a constraint
        for i in range(1, n + 1):
            if a[i] != -1:  # If there's a constraint at position i
                need_place = a[i] - a[pi]  # Number of values to place after pi that are <= i
                ways = 0
                for place_below_pi in range(need_place + 1):  # Try all placements below pi
                    cways = ways_mat(i - pi, pi - a[pi], place_below_pi)  # Compute combinations
                    cways *= ways_mat(i - a[pi] - place_below_pi, i - pi, need_place - place_below_pi)  # Multiply
                    cways %= MOD  # Modular arithmetic
                    ways += cways  # Sum up all valid ways
                ans = ans * ways % MOD  # Multiply total ways
                pi = i  # Update previous index
    print(ans)


# https://github.com/VaHiX/CodeForces/