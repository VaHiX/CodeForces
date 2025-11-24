# Problem: CF 2122 E - Greedy Grid Counting
# https://codeforces.com/contest/2122/problem/E

"""
E. Greedy Grid Counting

Purpose:
This code solves a dynamic programming problem on a 2×n grid where each cell has a value between 1 and k,
and some cells are empty (-1). The goal is to count the number of ways to fill these empty cells such that
in every subgrid, there exists at least one greedy path (moving only right or down, choosing the neighbor
with greater value) that reaches the maximum possible value.

Algorithm:
- Dynamic Programming with State Compression:
  - At each column, track how many ways we can form paths with specific differences between top and bottom values.
  - The state represents the number of valid configurations reaching each relative difference (top-bottom) at current step.
  - Use rolling arrays to optimize space.

Time Complexity:
O(n * k^2), where n is the number of columns, and k is the range of integers.

Space Complexity:
O(k), due to using a one-dimensional array of size k+1 for intermediate states.
"""

import sys

input = sys.stdin.readline
MOD = 998244353
t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    state = [0] * (k + 1)
    if a[0] == -1:
        state[k] = k
    else:
        state[k] = 1
    for i in range(n - 1):
        nex = [0] * (k + 1)
        u = b[i]
        v = a[i + 1]
        tot = sum(state) % MOD
        if u == -1 and v == -1:
            # Both cells are empty, all differences from (-k+1) to (k-1) are valid
            for d in range(1 - k, k):
                ct = k - abs(d)
                if d >= 0:
                    # d >= 0: shift forward in the array
                    for i in range(d, k):
                        nex[i - d] += ct * state[i]
                    nex[k] += ct * state[k]
                else:
                    # d < 0: add total to corresponding index
                    nex[-d] += ct * tot
        elif u == -1:
            # Only top cell is empty, compute valid transitions accordingly
            for d in range(v - k, v):
                ct = 1
                if d >= 0:
                    for i in range(d, k):
                        nex[i - d] += ct * state[i]
                    nex[k] += ct * state[k]
                else:
                    nex[-d] += ct * tot
        elif v == -1:
            # Only bottom cell is empty, compute valid transitions accordingly
            for d in range(1 - u, k + 1 - u):
                ct = 1
                if d >= 0:
                    for i in range(d, k):
                        nex[i - d] += ct * state[i]
                    nex[k] += ct * state[k]
                else:
                    nex[-d] += ct * tot
        else:
            # Both fixed: exact difference is fixed
            d = v - u
            ct = 1
            if d >= 0:
                for i in range(d, k):
                    nex[i - d] += ct * state[i]
                nex[k] += ct * state[k]
            else:
                nex[-d] += ct * tot
        state = [v % MOD for v in nex]
    out = sum(state) % MOD
    if b[-1] == -1:
        out *= k
    print(out % MOD)


# https://github.com/VaHiX/CodeForces/