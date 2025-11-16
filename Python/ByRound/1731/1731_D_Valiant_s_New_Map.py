# Problem: CF 1731 D - Valiant's New Map
# https://codeforces.com/contest/1731/problem/D

"""
Algorithm: Binary Search on Answer + Dynamic Programming
Purpose: Find the largest square subgrid where all elements are >= side length of the square.

Time Complexity: O(n * m * log(min(n,m)))
Space Complexity: O(n * m)

Approach:
- Use binary search on the possible square side lengths (from 1 to min(n,m)).
- For each candidate side length 'l', use a dynamic programming approach to check if a valid square of size 'l' exists.
  - The DP state dp[i][j] represents the largest square ending at position (i-1, j-1) with all elements >= l.
  - If grid[i-1][j-1] >= l, then dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1])
  - If dp[i][j] >= l, then a valid square of size l exists.
"""

def check(grid, n, m, x):
    # Create a DP table initialized with zeros
    dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
    
    # Fill the DP table
    for i in range(n):
        for j in range(m):
            # If current cell height is less than x, no valid square can end here
            if grid[i][j] < x:
                dp[i + 1][j + 1] = 0
                continue
            # Compute the size of the largest square ending at this cell
            dp[i + 1][j + 1] = 1 + min(dp[i + 1][j], dp[i][j], dp[i][j + 1])
            # If we found a valid square of size x or more, return True
            if dp[i + 1][j + 1] >= x:
                return True
    return False


for _ in range(int(input())):
    n, m = map(int, input().split())
    grid = []
    for i in range(n):
        grid.append(list(map(int, input().split())    ))

    ans = 1
    l, r = 1, min(n, m)

    # Binary search on the answer
    while l <= r:
        mid = (l + r) // 2
        if check(grid, n, m, mid):
            ans = mid
            l = mid + 1
        else:
            r = mid - 1

    print(ans)


# https://github.com/VaHiX/CodeForces/