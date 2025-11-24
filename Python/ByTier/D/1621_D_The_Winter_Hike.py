# Problem: CF 1621 D - The Winter Hike
# https://codeforces.com/contest/1621/problem/D

"""
Code Purpose:
This code solves the problem of finding the minimum cost to move friends from the top-left corner 
to the bottom-right corner of a 2n x 2n grid, by removing snow from certain cells and applying 
instructions to move friends. The strategy involves calculating the cost to remove snow from 
the destination cells (bottom-right quadrant) and then adding the minimal cost among specific 
corner cells that might be used to guide the friends.

Algorithms/Techniques:
- Greedy approach to minimize cost
- Preprocessing of cost matrix to determine minimum path
- Observation that friends can move through rows/columns, so the problem reduces to 
  selecting the cheapest way to move from the top-left area to the bottom-right area

Time Complexity: O(n^2) due to iterating over a 2n x 2n grid once for summing costs  
Space Complexity: O(n^2) for storing the cost matrix
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    c = []
    for _ in range(n * 2):
        l = list(map(int, input().split()))
        c.append(l)
    # Sum up the cost of removing snow from all cells in the bottom-right quadrant (n x n)
    ans = 0
    for i in range(n, 2 * n):
        for j in range(n, 2 * n):
            ans += c[i][j]
    # Find the minimum cost among the specific corner cells that could be used as entry points
    # These corners represent strategic positions for moving friends from top-left to bottom-right
    tmp = min(
        c[0][n],      # Top-left to bottom-right
        c[n][0],      # Top-left to bottom-right  
        c[0][-1],     # Top-right to bottom-left
        c[-1][0],     # Bottom-left to top-right
        c[n - 1][n],  # Bottom-left corner
        c[n - 1][-1], # Bottom-right corner
        c[n][n - 1],  # Top-right corner
        c[-1][n - 1], # Bottom-left corner 
    )
    print(ans + tmp)


# https://github.com/VaHiX/CodeForces/