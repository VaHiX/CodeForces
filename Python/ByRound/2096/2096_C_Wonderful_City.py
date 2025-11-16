# Problem: CF 2096 C - Wonderful City
# https://codeforces.com/contest/2096/problem/C

"""
C. Wonderful City

Purpose:
This problem involves making a city grid beautiful by ensuring no two adjacent buildings (horizontally or vertically) have the same height. 
To achieve this, we can hire workers from two companies: 
- Company A increases all heights in a row by 1.
- Company B increases all heights in a column by 1.

We use dynamic programming to determine the minimum cost of hiring workers to make the grid beautiful.

Approach:
1. Use DP on each row to track the minimal cost for ending with either "no change" or "row changed".
2. For each step, calculate the change needed to ensure adjacent buildings don't have same height.
3. After processing, transpose the grid and repeat the process for columns using the second array of costs.
4. If the final answer is too large (>= 1e18), return -1 indicating impossibility.

Time Complexity: O(n^2) per test case due to double nested loop for DP and transposition.
Space Complexity: O(n^2) for storing the heights grid, plus O(n) for arrays.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Grid Transposition
"""

def solve():
    n = int(input())
    heights = [list(map(int, input().split())) for i in range(n)]
    arr = list(map(int, input().split()))
    brr = list(map(int, input().split()))
    ans = 0
    for _ in range(2):  # Two passes: rows then columns (with transposed grid)
        dp0 = 0  # DP state: cost when no change in current row/column
        dp1 = arr[0]  # DP state: cost when change is made in current row/column
        for i in range(1, n):
            ndp0 = ndp1 = 10**18  # New DP states initialized to infinity
            d = [heights[i][j] - heights[i - 1][j] for j in range(n)]
            # Compute changes needed between consecutive rows/columns
            if 0 not in d:  # No same heights -> no conflict when not changing
                ndp0 = min(ndp0, dp0)  # Keep state (no change)
                ndp1 = min(ndp1, dp1 + arr[i])  # Change current row (add cost)
            if 1 not in d:  # Conflict exists if we increase by 1
                ndp0 = min(ndp0, dp1)  # Previous was changed -> current must be unchanged
            if -1 not in d:  # Conflict exists if we decrease by 1
                ndp1 = min(ndp1, dp0 + arr[i])  # Previous was unchanged -> current changed
            dp0, dp1 = ndp0, ndp1  # Move to next iteration with updated states
        ans += min(dp0, dp1)
        # Transpose grid for next pass (processing columns as rows)
        for i in range(n):
            for j in range(i + 1, n):
                heights[i][j], heights[j][i] = heights[j][i], heights[i][j]
        arr = brr  # Switch to column cost array
    if ans >= 10**18:
        return -1
    return ans


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())


# https://github.com/VaHiX/codeForces/