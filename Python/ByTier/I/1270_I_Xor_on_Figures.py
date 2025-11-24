# Problem: CF 1270 I - Xor on Figures
# https://codeforces.com/contest/1270/problem/I

# -*- coding: utf-8 -*-
"""
Problem: XOR on Figures

This code solves a problem where we have a 2^k x 2^k grid filled with integers, and we want to reduce all values to zero using specific operations.

Each operation involves placing a given figure (a set of cells) onto the grid and XORing all values in those cells with a chosen integer p.

The algorithm uses:
1. A simulation approach with bit manipulation
2. Fast exponentiation-like processing where we double the figure positions each step
3. Efficiently tracking the effect of operations on the entire grid using iterative updates

Time Complexity: O(k * 4^k)
Space Complexity: O(4^k)

Algorithm:
- Process operations in log(2^k) = k steps
- In each step, we double the size of the figure and apply XOR to all cells using a sliding window approach on toroidal grid
- Use a two-dimensional array with only two layers for efficiency
"""

k = int(input())
dim = 1 << k
grid = [[[0] * dim for _ in range(dim)] for _ in range(2)]
for i in range(dim):
    grid[0][i] = list(map(int, input().split()))
t = int(input())
fig = []
for _ in range(t):
    x, y = map(int, input().split())
    fig.append((x - 1, y - 1))  # Convert to 0-indexed

# Process k steps
for q in range(k):
    # For each cell in the grid, compute XOR based on figure
    for i in range(dim):
        for j in range(dim):
            grid[1 - q & 1][i][j] = 0  # Initialize result to 0
            for p in fig:
                x = (i - p[0]) % dim   # Get relative position modulo dim
                y = (j - p[1]) % dim   # Get relative position modulo dim
                grid[1 - q & 1][i][j] ^= grid[q & 1][x][y]  # Apply XOR with value from source cell
    
    # Double the figure size by scaling each point by 2 (mod dim)
    for i in range(t):
        fig[i] = (fig[i][0] * 2 % dim, fig[i][1] * 2 % dim)

# Count number of non-zero elements in final state
ans = 0
for i in range(dim):
    for j in range(dim):
        if grid[k & 1][i][j]:  # If current value is not zero
            ans += 1
print(ans)


# https://github.com/VaHiX/codeForces/