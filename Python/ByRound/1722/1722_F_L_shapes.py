# Problem: CF 1722 F - L-shapes
# https://codeforces.com/contest/1722/problem/F

"""
Code Purpose:
This code determines whether a given grid of '*' and '.' characters can be completely 
covered by L-shapes, where each L-shape consists of exactly 3 '*' cells arranged in 
an L-shape configuration, and no two L-shapes can touch each other at edges or corners.

Algorithms/Techniques:
- Iteration over the grid to find all '*' cells.
- For each '*' cell, examine its immediate neighbors (within 2x2 region).
- Validate that the neighbors form a valid L-shape (exactly 2 neighbors, and they are 
  within one unit distance from each other).
- Check that no two L-shapes are adjacent by edge or corner.
- Output "YES" if valid, "NO" otherwise.

Time Complexity: O(n * m), where n is number of rows and m is number of columns.
Space Complexity: O(1), excluding input storage.
"""

for i in range(int(input())):  # Process each test case
    n, m = map(int, input().split())  # Read grid dimensions
    M = [input() for j in range(n)]  # Read grid
    v = False  # Flag to indicate if grid is invalid
    for j in range(n):  # Iterate through rows
        for k in range(m):  # Iterate through columns
            if M[j][k] == "*":  # If current cell is part of an L-shape
                L = []  # List to store neighbors of current cell
                # Check neighbors in a 3x3 region around current cell
                for x in range(max(0, j - 1), min(n, j + 2)):
                    for y in range(max(0, k - 1), min(m, k + 2)):
                        if M[x][y] == "*" and (x, y) != (j, k):  # If neighbor is '*'
                            L.append((x, y))  # Add neighbor to list
                # Validate if neighbors form a valid L-shape:
                # - Exactly 2 neighbors
                # - Distance between neighbors is at most 1 (to ensure they form L)
                if (
                    len(L) != 2
                    or max(abs(L[0][0] - L[1][0]), abs(L[0][1] - L[1][1])) > 1
                ):
                    v = True  # Mark invalid
                    break  # Exit inner loop
    print("YNEOS"[v::2])  # Print "YES" if v is False, else "NO"


# https://github.com/VaHiX/CodeForces/