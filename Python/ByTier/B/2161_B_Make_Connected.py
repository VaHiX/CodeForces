# Problem: CF 2161 B - Make Connected
# https://codeforces.com/contest/2161/problem/B

"""
Algorithm: Make Connected
Techniques: Grid analysis, coordinate checking

Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) due to storing coordinates of black cells

The problem requires determining if a configuration of black and white cells in an n x n grid 
can be made connected (all black cells orthogonally connected) while also ensuring no three 
consecutive black cells are aligned vertically or horizontally.

Approach:
1. Collect all black cell coordinates.
2. Check conditions that allow solution:
   - If no black cells exist, we can color one white cell black.
   - If we can connect all black cells in a small area (no more than 1 unit in either dimension).
   - If all black cells lie on at most 2 diagonals (either main or anti-diagonal).

This logic leverages coordinate relationships and constraints.
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    grid = []
    for _ in range(n):
        grid.append(str(input()).strip())
    x = []
    y = []
    dp = []  # Main diagonal (i + j)
    dn = []  # Anti-diagonal (i - j)
    for i in range(n):
        for j in range(n):
            if grid[i][j] == "#":
                dp.append(i + j)
                dn.append(i - j)
                x.append(i)
                y.append(j)

    # If there are no black cells, we can paint one white cell black to satisfy condition 1
    if x == []:
        return "YES"
    
    # If all black cells form a small connected region (at most 1 unit in x and y direction)
    if (max(x) - min(x) <= 1 and max(y) - min(y) <= 1):
        return "YES"
    
    # If all black cells lie on at most two diagonals (main or anti)
    if (max(dp) - min(dp) <= 1 or max(dn) - min(dn) <= 1):
        return "YES"
    
    return "NO"


tt = int(input())
for _ in range(tt):
    ans = solve()
    print(ans)


# https://github.com/VaHiX/CodeForces/