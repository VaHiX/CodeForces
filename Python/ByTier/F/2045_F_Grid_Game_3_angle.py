# Problem: CF 2045 F - Grid Game 3-angle
# https://codeforces.com/contest/2045/problem/F

"""
F. Grid Game 3-angle

This problem is a variant of a combinatorial game theory problem, specifically related to Nim-like games on a triangular grid.

The key idea is to use the Sprague-Grundy theorem and XOR operations (nim-sum) for determining winning/losing positions.
The game can be modeled as a sum of independent nim-heaps. For each row r in the triangle:
- All cells in that row are processed with their stone counts
- The effect of moves in one cell affects a triangular region below it
- To simplify this, we can consider only the "difference" or XOR of state values across rows due to the nature of Nim operations

We process all stones by considering their row and applying modulo K+1 arithmetic.
Then, for each row (after modulo), we compute XOR of stone values for that row.
Finally, if the total XOR of all such values is 0 -> second player (Kamu) wins; otherwise first player (Anda) wins.

Time Complexity: O(M)
Space Complexity: O(K)

"""

import sys

input = sys.stdin.readline
from collections import defaultdict

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    seen = defaultdict(int)
    for _ in range(m):
        ri, ci, xi = map(int, input().split())
        # Apply modulo K+1 to both row and stone count to reduce state space
        ri %= k + 1
        xi %= k + 1
        # XOR operation to accumulate the nim-sum for each row (mod K+1)
        seen[ri] ^= xi
    o = 0
    # Sum up all XOR'd values (nim-sum)
    for v in seen:
        o += seen[v]
    # If total XOR is non-zero, first player (Anda) wins; else second (Kamu)
    if o:
        print("Anda")
    else:
        print("Kamu")


# https://github.com/VaHiX/codeForces/