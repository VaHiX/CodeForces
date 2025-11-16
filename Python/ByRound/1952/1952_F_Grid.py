# Problem: CF 1952 F - Grid
# https://codeforces.com/contest/1952/problem/F

"""
F. Grid
Algorithms/Techniques: Brute Force, Sliding Window (2D)
Time Complexity: O(n^2) where n = 21, so effectively O(1)
Space Complexity: O(n^2) for storing the grid

This code finds the maximum sum of a 4x4 subgrid within a 21x21 grid.
It iterates through all possible 4x4 windows in the grid and calculates
their sums to find the maximum.
"""

n = 21
a = [[int(i) for i in input()] for _ in range(n)]  # Read the 21x21 grid of 0s and 1s
ans = 0
for x in range(n - 3):  # Loop through all valid starting x-coordinates for 4x4 subgrid
    for y in range(n - 3):  # Loop through all valid starting y-coordinates for 4x4 subgrid
        res = 0
        for dx in range(4):  # Iterate over rows of the 4x4 window
            for dy in range(4):  # Iterate over columns of the 4x4 window
                res += a[x + dx][y + dy]  # Add element at current position to running sum
        ans = max(ans, res)  # Keep track of maximum sum found so far
print(ans)


# https://github.com/VaHiX/codeForces/