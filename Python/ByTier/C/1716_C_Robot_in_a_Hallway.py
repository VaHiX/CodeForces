# Problem: CF 1716 C - Robot in a Hallway
# https://codeforces.com/contest/1716/problem/C

"""
Purpose: Solve the robot movement problem in a 2xM grid where the robot must visit all cells
         in minimum time, considering each cell unlocks at a specific time and the robot
         can only move to unlocked cells.

Algorithms/Techniques:
- Dynamic Programming with preprocessing of suffix maximums
- Greedy approach with careful time tracking
- Bit manipulation for alternating row indexing

Time Complexity: O(m) per test case
Space Complexity: O(m) for the suffix arrays and auxiliary variables
"""

INF = 2 * 10**9

for _ in range(int(input())):
    m = int(input())
    a = [[int(x) for x in input().split()] for i in range(2)]
    su = [[-INF for j in range(m + 1)] for i in range(2)]
    # Precompute suffix maximums for each row
    for i in range(2):
        for j in range(m - 1, -1, -1):
            # su[i][j] stores the maximum time needed to reach from column j to end,
            # considering the constraints of movement and unlocking times
            su[i][j] = max(su[i][j + 1] - 1, a[i][j], a[i ^ 1][j] - (2 * (m - j) - 1))
    
    pr = a[0][0] - 1  # Previous time to reach the current column from top row
    ans = INF
    # Iterate through all possible ending columns
    for j in range(m):
        jj = j & 1  # Determine row (0 or 1) based on column index
        # Calculate minimum time required to go through the path ending at column j
        ans = min(ans, max(pr, su[jj][j + 1] - 2 * j - 1, a[jj ^ 1][j] - 2 * m + 1))
        # Update pr to account for the time to get from the bottom row
        pr = max(pr, a[jj ^ 1][j] - 2 * j - 1)
        # Another path consideration
        ans = min(ans, max(pr, su[jj ^ 1][j + 1] - 2 * j - 2))
        # Update pr if there's an onward move available (only if not last column)
        if j < m - 1:
            pr = max(pr, a[jj ^ 1][j + 1] - 2 * j - 2)
    # Add total number of moves (2*m) to the answer for the final time
    print(ans + 2 * m)


# https://github.com/VaHiX/CodeForces/