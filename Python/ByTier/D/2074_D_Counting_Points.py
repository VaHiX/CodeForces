# Problem: CF 2074 D - Counting Points
# https://codeforces.com/contest/2074/problem/D

"""
D. Counting Points

Purpose:
This program counts the number of integer lattice points (x, y) that lie inside or on the border of at least one of the given circles.
Each circle is defined by its center (xi, 0) on the x-axis and a radius ri.

Approach:
1. For each circle, iterate through all integer x-values within the circle's horizontal range.
2. For each such x-value, compute the maximum y-coordinate (in absolute value) that lies within the circle using the formula: y = sqrt(r^2 - (x - center)^2).
3. Store for each x-coordinate the maximum height of coverage from all circles overlapping it.
4. The total number of points is twice the sum of these heights (accounting for positive and negative y-values), plus the count of distinct x-coordinates (for y=0).

Algorithms/Techniques:
- Geometry + Coordinate Compression
- Iterative Coverage Calculation using Pythagorean theorem

Time Complexity: O(m * log(m)) where m is the sum of radii, due to the scanning over radii and use of sqrt.
Space Complexity: O(m) for storing height map.

Input Format:
- First line: number of test cases t
- For each case: n (number of circles), m (sum of radii)
- Next two lines: centers and radii

Output:
- Number of integer points covered by at least one circle.
"""

import sys
from math import isqrt

input = sys.stdin.readline
for _ in range(int(input())):
    input()  # skip n, m as they are not used directly
    height = {}
    # Process centers and radii for all circles
    for center, radius in zip(map(int, input().split()), map(int, input().split())):
        # Iterate over x-coordinates that can be covered by this circle
        for d in range(-radius, radius + 1):
            x = d - center  # actual x coordinate
            # Compute max y value such that point (x,y) is inside or on the circle
            height[x] = max(height.get(x, 0), isqrt(radius * radius - d**2))
    # Final result: multiply sum of heights by 2 (positive and negative y),
    # then add number of distinct x values (y=0 case)
    print(sum(height.values()) * 2 + len(height))


# https://github.com/VaHiX/codeForces/