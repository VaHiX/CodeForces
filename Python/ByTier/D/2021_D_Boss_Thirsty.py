# Problem: CF 2021 D - Boss, Thirsty
# https://codeforces.com/contest/2021/problem/D

"""
D. Boss, Thirsty

Problem Description:
Given a grid of n rows and m columns, each cell A[i][j] represents the profit of selling drink j on day i.
On each day, we must select a contiguous subarray of drinks to sell (i.e., sell drinks from index l to r inclusive).
The selection for day i (where i > 1) must satisfy:
- At least one drink type sold on day i was also sold on day i-1.
- At least one drink type sold on day i was not sold on day i-1.

Goal: Maximize the total profit across all n days.

Algorithms/Techniques:
Dynamic Programming with Forward and Backward Passes:
- For each day, compute maximum profit ending at each column when moving forward.
- Similarly compute for backward direction.
- Use transition states to ensure constraint of overlapping and non-overlapping drinks between days.
- This approach efficiently tracks best paths while respecting the constraints using suffix and prefix computations.

Time Complexity: O(n * m)
Space Complexity: O(m)

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
INF = 1 << 63


def solve_case():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(n)]
    
    # dp_right[i] stores max profit ending at column i when going forward
    dp_right = [0] * m
    total = 0
    for i in range(m):
        dp_right[i] = total = max(0, total) + a[0][i]
    
    # dp_left[i] stores max profit ending at column i when going backward
    dp_left = [0] * m
    total = 0
    for i in range(m - 1, -1, -1):
        dp_left[i] = total = max(0, total) + a[0][i]
    
    # Process from second row onwards
    for r in range(1, n):
        dp_right_new = [0] * m
        dp_right_new[0] = -INF  # No valid previous path to first column
        
        # Forward pass for current row (left to right)
        total = a[r][0]
        for c in range(1, m):
            # Take max of either continuing from left or combining with prior best valid state
            dp_right_new[c] = (
                max(dp_right_new[c - 1], total + max(dp_right[c - 1], dp_left[c]))
                + a[r][c]
            )
            total = max(0, total) + a[r][c]
        
        dp_left_new = [0] * m
        dp_left_new[m - 1] = -INF  # No valid previous path to last column

        # Backward pass for current row (right to left)
        total = a[r][m - 1]
        for c in range(m - 2, -1, -1):
            # Take max of either continuing from right or combining with prior best valid state
            dp_left_new[c] = (
                max(dp_left_new[c + 1], total + max(dp_right[c], dp_left[c + 1]))
                + a[r][c]
            )
            total = max(0, total) + a[r][c]
        
        # Update DP arrays for next iteration
        dp_right = dp_right_new
        dp_left = dp_left_new
    
    # Return maximum profit from either direction
    ans = max(max(dp_left), max(dp_right))
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/