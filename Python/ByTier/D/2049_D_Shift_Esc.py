# Problem: CF 2049 D - Shift + Esc
# https://codeforces.com/contest/2049/problem/D

"""
Algorithm: Dynamic Programming with Optimization
Techniques: 
    - 2D Dynamic Programming with row shifting optimization
    - For each row, we precompute all possible shifts and update DP accordingly
    - Time Complexity: O(n * m^2) per test case
    - Space Complexity: O(n * m)

The approach uses a 2D DP table where dp[i][j] represents the minimum cost to reach cell (i, j).
Before moving, we can perform cyclic shifts on rows. Each shift contributes 'cost' to the total.
We process rows one by one, and for each row, we compute all possible shifts and update the DP accordingly.
This method allows for efficient computation of the optimal path while considering row shifts.
"""
for _ in range(int(input())):
    n, m, cost = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(n)]

    # Initialize DP table with large values
    ans = [[10**12] * (m + 1) for _ in range(n + 1)]

    # Base case
    ans[0][1] = 0

    for i in range(1, n + 1):
        # Accumulated cost for shifts so far
        curr = 0
        # Temporary array to store updated values
        currans = [10**12] * (m + 1)
        for j in range(1, m + 1):
            # Compute all possible shifts for the current row
            # This simulates shifting the row by (j-1) positions to the left
            for k in range(1, m + 1):
                # Value at shifted position + minimum of:
                # 1. Previous shift result from same column (currans[k-1])
                # 2. Cost from above row with shifted column arrangement (ans[i-1][k])
                currans[k] = grid[i - 1][(k - 1 + (j - 1)) % m] + min(
                    currans[k - 1], curr + ans[i - 1][k]
                )
                ans[i][k] = min(ans[i][k], currans[k])
            curr += cost  # Increase cost for each additional shift

    print(ans[n][m])


# https://github.com/VaHiX/CodeForces/