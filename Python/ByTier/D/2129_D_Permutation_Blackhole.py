# Problem: CF 2129 D - Permutation Blackhole
# https://codeforces.com/contest/2129/problem/D

"""
D. Permutation Blackhole

Purpose: This code counts how many permutations of a given length can produce a specified coloring sequence,
where the coloring is determined by a process involving black cells and scoring based on proximity
to previously colored black cells.

Algorithms & Techniques:
- Dynamic Programming with memoization
- Recursion with state tracking (l, r, u, v) representing subproblem boundaries and constraints
- Combinatorial calculations using precomputed Pascal's triangle for binomial coefficients

Time Complexity: O(n^4) per test case due to nested recursion and state memoization,
where n is the length of input permutation.

Space Complexity: O(n^2) for storing Pascal triangle and memoization states.

"""

import sys

sys.setrecursionlimit(10000)
MOD = 998244353
PI = 3.141592653589793
EPS = 1e-7

n = 0
s = []
memo = {}
pasc = [[0] * 200 for _ in range(200)]


def calc(l, r, u, v):
    """
    Recursive function to calculate number of valid permutations for a given subproblem.
    l, r: left and right indices defining the current segment
    u, v: constraints on minimum scores for the left and right segments
    """
    ind = (l, r, u, v)
    if ind in memo:
        return memo[ind]
    if r == l + 1:  # Base case: only one element in this subsegment
        if u == 0 or u == -1:  # If no constraint or allowed minimum is zero
            if v == 0 or v == -1:
                return 1
        return 0
    out = 0
    for k in range(l + 1, r):  # Try all possible split points k within segment (l,r)
        uu = u
        vv = v
        if (l != 0) and ((r == n + 1) or ((k - l) <= (r - k))):  # Left side constraint
            if uu == 0:
                continue  # Skip invalid splits
            if uu != -1:
                uu -= 1  # Decrease constraint by 1
        elif r <= n:  # Right side constraint
            if vv == 0:
                continue  # Skip invalid splits
            if vv != -1:
                vv -= 1  # Decrease constraint by 1
        if s[k] == -1:  # If k-th place is undetermined
            add = calc(l, k, uu, -1) * calc(k, r, -1, vv)
            add = (add % MOD) * pasc[k - l - 1][r - k - 1]
            out += add
            out %= MOD
        else:  # If k-th place is determined
            for z in range(min(s[k] + 1, 14)):  # Try all possible scores up to s[k]
                add = calc(l, k, uu, z) * calc(k, r, s[k] - z, vv)
                add = (add % MOD) * pasc[k - l - 1][r - k - 1]
                out += add
                out %= MOD
    memo[ind] = out
    return out


def solve():
    global n, s, memo
    n = int(input())
    s = [0] * (n + 1)
    memo = {}
    arr = list(map(int, input().split()))
    for i in range(1, n + 1):
        s[i] = arr[i - 1]
        if s[i] > 12:
            print(0)
            return
    tot = sum(max(0, x) for x in s[1:])
    if tot > n - 1:
        print(0)
        return
    out = calc(0, n + 1, -1, -1)
    print(out)


# Precompute Pascal's triangle for use in calculating combinations
for i in range(200):
    for j in range(200):
        if i == 0 or j == 0:
            pasc[i][j] = 1
        else:
            pasc[i][j] = (pasc[i][j - 1] + pasc[i - 1][j]) % MOD

t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/