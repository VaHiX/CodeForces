# Problem: CF 2121 C - Those Who Are With Us
# https://codeforces.com/contest/2121/problem/C

"""
C. Those Who Are With Us

Algorithm:
- The problem asks us to minimize the maximum value in a matrix after performing exactly one operation.
- Operation: Choose a row r and column c, then decrease all elements in row r or column c by 1.
- Key insight: For any given position (i,j), if we perform an operation on row r = i or column c = j,
  the value at that position decreases by 1. The total effect on a cell (i,j) is determined by whether
  its row or column was selected for the operation.

Time Complexity: O(n * m)
Space Complexity: O(n + m)

Approach:
1. Find the maximum value in the grid.
2. Count how many times this maximum occurs in the grid.
3. For each cell with maximum value, increment counters for its row and column (to track overlaps).
4. Iterate over all cells to find if selecting a certain row/column pair reduces the max.
5. If such a pair exists, return max - 1; otherwise, return max.

"""

import sys

input = sys.stdin.readline


def solve():
    n, m = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(n)]
    mx = max([max(x) for x in grid])  # Find maximum value
    count = sum([grid[i].count(mx) for i in range(n)])  # Count how many times max appears
    
    # Initialize row and column counters to track number of max values in each row/column
    rows = [0 for _ in range(n)]
    cols = [0 for _ in range(m)]
    
    # Count max values per row and column
    for i in range(n):
        for j in range(m):
            if grid[i][j] == mx:
                rows[i] += 1
                cols[j] += 1

    # Try all possible operations
    for i in range(n):
        for j in range(m):
            # If this cell contributes to a row/column that is selected,
            # it will be decremented if we choose that row or column
            if rows[i] + cols[j] - (grid[i][j] == mx) == count:
                return mx - 1  # We can reduce maximum by choosing row i and col j

    return mx  # If no operation leads to a better result


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/