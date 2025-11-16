# Problem: CF 1799 E - City Union
# https://codeforces.com/contest/1799/problem/E

"""
Code Purpose:
This code solves the problem of connecting two cities on a grid with minimum number of filled cells,
such that the resulting grid forms a single city and the shortest path between any two filled cells
equals their Manhattan distance.

Approach:
1. Identify bounding rectangles for each city (leftmost, rightmost, topmost, bottommost filled cells)
2. Try to connect the two cities by filling cells in a way that maintains Manhattan distance property
3. The approach tries to make a "bridge" between the two cities by filling all cells in a rectangular region
   between their bounding boxes.

Algorithms/Techniques:
- Grid manipulation and bounding box calculation
- Iterative filling to connect components
- Manhattan distance constraint enforcement

Time Complexity: O(n * m) per test case, where n and m are grid dimensions
Space Complexity: O(n * m) for storing the grid and auxiliary arrays
"""

import io
import os
import sys

try:
    Z = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
except:
    Z = lambda: sys.stdin.readline().encode()
Y = lambda: map(int, Z().split())


def disp(a):
    E = []
    for i in range(n):
        E.append("".join(".#"[a[i][j]] for j in range(m)))
    E.append("")
    print("\n".join(E))


def solve(n, m, a):
    # Arrays to store leftmost and rightmost filled columns for each row
    lx = [-1] * n
    hx = [-1] * n
    # Arrays to store topmost and bottommost filled rows for each column
    ly = [-1] * m
    hy = [-1] * m
    
    # Find bounding boxes for each city
    for i in range(n):
        for j in range(m):
            if a[i][j]:
                if lx[i] == -1:
                    lx[i] = j
                hx[i] = j
                if ly[j] == -1:
                    ly[j] = i
                hy[j] = i
    
    # Merge bounding boxes of two cities
    cl = ch = -1
    for i in range(n):
        if lx[i] != -1:
            if cl == -1:
                cl = lx[i]
                ch = hx[i]
            else:
                if hx[i] > ch:
                    if lx[i] > ch:
                        lx[i] = ch
                    ch = hx[i]
                if lx[i] < cl:
                    if hx[i] < cl:
                        hx[i] = cl
                    cl = lx[i]
    
    # Fill the region between two cities
    for _ in range(2):  # Two passes to make sure connection is solid
        for i in range(n):
            if lx[i] != -1:
                for j in range(lx[i], hx[i] + 1):
                    a[i][j] = 1  # Fill cells in region
                    if ly[j] == -1 or ly[j] > i:
                        ly[j] = i  # Update column bounds
                    if hy[j] < i:
                        hy[j] = i
        for j in range(m):
            if ly[j] != -1:
                for i in range(ly[j], hy[j] + 1):
                    a[i][j] = 1  # Fill cells in region
                    if lx[i] == -1 or lx[i] > j:
                        lx[i] = j  # Update row bounds
                    if hx[i] < j:
                        hx[i] = j
    
    return a


O = []
for _ in range(*Y()):
    n, m = Y()
    a = [[0] * m for i in range(n)]
    for i in range(n):
        s = Z().strip()
        for j in range(m):
            a[i][j] = s[j] == 35  # Convert '#' to 1 and '.' to 0
    a = solve(n, m, a)
    for i in range(n):
        O.append("".join(".#"[a[i][j]] for j in range(m)))
    O.append("")
print("\n".join(O[:-1]))


# https://github.com/VaHiX/CodeForces/