# Problem: CF 1898 C - Colorful Grid
# https://codeforces.com/contest/1898/problem/C

"""
Code Purpose:
This program solves the problem of coloring segments in a grid such that there exists a walk of a specified length where no two consecutive segments have the same color.

The algorithm works by:
1. Determining if a solution exists based on parity and length constraints.
2. For valid cases, constructing a specific coloring pattern:
   - Horizontal segments are colored in a checkerboard pattern for the first row
   - Horizontal segments for the last row follow a mirrored pattern
   - Vertical segments are colored to ensure alternating colors in a specific way

Algorithms/Techniques:
- Parity checking to determine solvability: The key insight is that for a valid coloring to exist, the parity of (n XOR m XOR k) must be 0, and the total number of segments (n(m-1) + (n-1)m) must be at least k.
- Constructive coloring: The actual coloring uses alternating patterns for horizontal and vertical segments to ensure a valid walk exists.

Time Complexity: O(n*m) per test case, where n and m are the dimensions of the grid.
Space Complexity: O(n*m) to store the coloring output.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

t = int(input())
ans = []
for _ in range(t):
    n, m, k = map(int, input().split())
    # Check if solution is possible using parity and segment count constraint
    ans0 = "YES" if not (n ^ m ^ k) & 1 and n + m - 2 <= k else "NO"
    ans.append(ans0)
    if ans0 == "NO":
        continue
    ans0 = []
    for i in range(n):
        # First row: alternate colors starting with red
        ans1 = (
            ["R"] * (m - 1) if i else ["R" if not j & 1 else "B" for j in range(m - 1)]
        )
        # Last row: use a specific pattern (mirror of first)
        if i == n - 1:
            if n & 1:
                ans1 = ["R" if not j & 1 else "B" for j in range(m - 1)]
            else:
                ans1 = ["B" if not j & 1 else "R" for j in range(m - 1)]
        ans0.append(" ".join(ans1))
    # Vertical segments: color such that alternating property holds
    ans1 = ["B"] * m
    for i in range(n - 1):
        ans1[-1] = "R" if (i ^ m) & 1 else "B"
        if i:
            ans1[0] = "R" if not i & 1 else "B"
        ans0.append(" ".join(ans1))
    ans.append("\n".join(ans0))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/