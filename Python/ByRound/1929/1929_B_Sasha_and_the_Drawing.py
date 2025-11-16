# Problem: CF 1929 B - Sasha and the Drawing
# https://codeforces.com/contest/1929/problem/B

"""
Code Purpose:
This code solves the problem of finding the minimum number of cells to color in an n×n grid such that at least k diagonals contain at least one colored cell. 

The approach is based on the observation that:
- A grid of size n×n has 4n−2 diagonals (2 main diagonals and 2 anti-diagonals).
- Each cell can cover at most 2 diagonals (one main and one anti-diagonal).
- To cover k diagonals optimally, we aim to minimize the number of cells used.

Algorithm:
- If k is less than or equal to 4n−4 (i.e. excluding the maximum case), then we can color at most 2 diagonals per cell, so we use ceil(k/2) cells.
- Special cases:
  - When k = 4n−3 (one short of max), we use (k//2)+1 cells.
  - When k = 4n−2 (maximum diagonals), we also use (k//2)+1 cells.

Time Complexity: O(1) - constant time for each test case.
Space Complexity: O(1) - only using a constant amount of space.
"""

import math


def solve():
    n, k = map(int, input().split())
    if k <= (4 * n - 4):
        # For most cases, we can cover k diagonals with ceil(k/2) cells
        ans = math.ceil(k / 2.0)
        print(ans)
    elif k == (4 * n - 3):
        # Special case: when k is one less than max diagonals
        print((k // 2) + 1)
    elif k == (4 * n - 2):
        # Special case: when k equals max diagonals
        print((k // 2) + 1)


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        solve()


# https://github.com/VaHiX/CodeForces/