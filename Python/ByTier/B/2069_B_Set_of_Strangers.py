# Problem: CF 2069 B - Set of Strangers
# https://codeforces.com/contest/2069/problem/B

"""
B. Set of Strangers

Purpose:
This code solves a problem where we are given an n x m grid of colors and need to find the minimum number of steps to make the entire grid the same color. In each step, we can select a set of "strangers" (non-adjacent cells) that all have the same color and repaint them with another color.

Algorithm:
1. For each unique color in the grid, determine the maximum number of steps needed to repaint all cells of that color.
2. The key insight is:
   - If a color appears in only one cell, it contributes 0 steps.
   - If a color appears in multiple cells, and those cells are not adjacent, we can paint them all in one step (we can choose a set of strangers of same color).
   - But if there are adjacent cells of the same color, then we may need more than one step.

Approach:
We use a 1D array `hash1` to count how many steps each color needs.
- For each cell in the grid:
  - Mark that color as appearing with at least 1 step (i.e., hash1[c] = max(hash1[c], 1))
  - If adjacent cells have same color, we increment that color's step requirement.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    x, y = map(int, input().split())
    final = [[*(map(int, input().split()))] for __ in range(x)]
    hash1 = (x * y + 1) * [0]
    for i in range(x):
        for j in range(y):
            c = final[i][j]
            hash1[c] = max(hash1[c], 1)  # Every color needs at least one step if present
            if i > 0 and final[i - 1][j] == c or j > 0 and final[i][j - 1] == c:
                # If this cell shares the same color with a neighbor from above or left,
                # we need an extra step to separate them.
                hash1[c] = 2
    vals = hash1
    if len(vals) == 1:
        print(0)
    else:
        print(sum(vals) - max(vals))


# https://github.com/VaHiX/codeForces/