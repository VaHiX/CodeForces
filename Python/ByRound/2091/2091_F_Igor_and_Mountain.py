# Problem: CF 2091 F - Igor and Mountain
# https://codeforces.com/contest/2091/problem/F

"""
F. Igor and Mountain
Algorithms/Techniques: Dynamic Programming with 2D Sliding Window + Prefix Sum Array

Time complexity: O(n * m * (d + sqrt(d^2 - 1)))
Space complexity: O(m)

The problem is solved using dynamic programming where we compute for each row,
the number of ways to reach each position on that row from valid positions in the previous rows.
We use a sliding window technique combined with prefix sums for efficient range queries.

We process the grid from bottom to top (row n-1 down to 0), updating the number of routes
that can end at each cell. For each level, we consider movement in two directions:
one with distance d and another with distance sqrt(d^2 - 1) due to the special conditions.
Prefix sums are used to compute sum of valid paths in a given range efficiently.
"""

import sys
from math import isqrt

input = sys.stdin.readline
MOD = 998244353

for _ in range(int(input())):
    gy, gx, d = map(int, input().split())
    diag = isqrt(d * d - 1)  # compute diagonal distance for special condition
    grid = [input() for _ in range(gy)]

    def step(curr_row, ways, dist):
        # Build prefix sum array to quickly compute range sums
        psa = [0]
        for num in ways:
            psa.append((psa[-1] + num) % MOD)
        
        # Update ways array using current row and sliding window with prefix sums
        for x in range(gx):
            ways[x] = (
                curr_row[x] == "X"
                and (psa[min(gx, x + dist + 1)] - psa[max(0, x - dist)]) % MOD
            )

    # Initialize last row with number of paths ending at each position
    ways = [int(c == "X") for c in grid[-1]]
    step(grid[-1], ways, d)  # apply first step based on distance d
    
    # Process rows from bottom to top
    for y in range(gy - 2, -1, -1):
        step(grid[y], ways, diag)  # apply step with diagonal distance
        step(grid[y], ways, d)     # apply step with regular distance
    total = 0
    for num in ways:
        total = (total + num) % MOD
    print(total)


# https://github.com/VaHiX/codeForces/