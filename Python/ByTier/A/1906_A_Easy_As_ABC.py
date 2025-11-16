# Problem: CF 1906 A - Easy As ABC
# https://codeforces.com/contest/1906/problem/A

"""
Problem: A. Easy As ABC
Purpose: Find the lexicographically smallest word of length 3 in a 3x3 grid,
         where each cell contains 'A', 'B', or 'C'. Words must be formed by
         traversing adjacent cells (including diagonals). 

Algorithms/Techniques:
    - Backtracking with DFS to explore all paths of length 3 starting from each cell.
    - For each starting cell, recursively build words and backtrack to try other paths.
    - Adjacent cells are defined using 8 directions including diagonals.

Time Complexity: O(1) - Since the grid is fixed at 3x3 and we only explore paths of length 3,
                     which results in at most 3 * 8^3 = 192 possible paths (very small constant).

Space Complexity: O(1) - The recursion depth is fixed at 3 (path length), 
                      and the visited set used for tracking path cells also has bounded size.
"""

arr = []
for i in range(3):
    arr.append(input())
dirs = [(0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)]
ans = ["CCC"]  # Initialize with maximum possible lexicographical string


def solve(s, i, j, h):
    # If current string length is less than 3, continue exploring neighbors
    if len(s) != 3:
        for x, y in dirs:  # Try all 8 directions
            # Check bounds and whether new cell is not already visited in this path
            if -1 < x + i < 3 and -1 < y + j < 3 and (x + i, y + j) not in h:
                # Recursively explore the next step with updated string and path
                solve(s + arr[i + x][j + y], i + x, j + y, h + [(i + x, j + y)])
    else:
        # If we have a 3-letter word, check if it's lexicographically smaller than current answer
        if ans[0] > s:
            ans[0] = s


# Try starting from each cell in the grid
for i in range(3):
    for j in range(3):
        solve(arr[i][j], i, j, [(i, j)])
print(ans[0])


# https://github.com/VaHiX/codeForces/