# Problem: CF 2009 D - Satyam and Counting
# https://codeforces.com/contest/2009/problem/D

"""
D. Satyam and Counting

Purpose:
This code counts the number of nondegenerate right triangles that can be formed
from a set of points on a 2D coordinate plane where all y-coordinates are either 0 or 1.
The algorithm works by separating points into two sets: those with y=0 (on x-axis) and y=1 (on line y=1).
It then uses the fact that for a right triangle to be formed:
- Two points must lie on one horizontal line
- One point must lie on the other horizontal line
- The angle between them at one of the endpoints must be 90 degrees

Techniques:
- Set-based lookup for fast membership checking
- Pairwise counting logic based on adjacent x-values for potential right angles

Time Complexity: O(n^2) in worst case due to nested loops, but optimized by using sets for fast lookups.
Space Complexity: O(n) for storing points in sets.

The algorithm exploits the fact that any valid right triangle will have:
- One vertex at (x, 0)
- One vertex at (x, 1)
- And another vertex at either (x±1, 0) or (x±1, 1), forming a 90-degree angle.
"""

import sys

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    n = int(input())
    x = set()  # Points with y = 0
    y = set()  # Points with y = 1
    for _ in range(n):
        a, b = map(int, input().split())
        if b:
            x.add(a)
        else:
            y.add(a)
    ans = 0
    for a in x:  # For each point on y=1 line
        if a in y:  # If there's also a point at same x-coordinate on y=0
            # Count triangles formed using this x-coordinate as shared point
            ans += len(x) - 1 + len(y) - 1
        if a - 1 in y and a + 1 in y:  # Special case where triangle is formed with neighbors
            ans += 1
    for a in y:  # For each point on y=0 line
        if a - 1 in x and a + 1 in x:  # If there's also a point at the same x-coordinate but on y=1
            ans += 1
    print(ans)


# https://github.com/VaHiX/codeForces/