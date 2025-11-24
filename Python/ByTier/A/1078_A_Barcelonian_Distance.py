# Problem: CF 1078 A - Barcelonian Distance
# https://codeforces.com/contest/1078/problem/A

"""
Problem: Minimal distance between two points in a grid with an additional diagonal avenue.

This problem uses a combination of Manhattan distance and geometric calculations to find 
the shortest path from point A to point B, considering that one can travel along:
1. Standard Manhattan grid streets (horizontal and vertical)
2. A special diagonal avenue defined by the line ax + by + c = 0

Approach:
- Calculate the base Manhattan distance between the two points.
- For every combination of points on the avenue (one from each of the two given points), 
  calculate the total travel distance:
  - Distance from A to a point on the avenue
  - Distance from that point on the avenue to B
  - Direct Euclidean distance between these two points on the avenue
- Return the minimum such calculated distance.

Time Complexity: O(1) - since we only check a fixed number of combinations (at most 4) 
Space Complexity: O(1) - constant space usage

Algorithms/Techniques:
- Manhattan Distance
- Euclidean Distance
- Geometric intersection of lines with grid
"""

import sys

input = sys.stdin.buffer.readline
from math import hypot


def worstCase(coordinate1, coordinate2):
    return abs(coordinate2[0] - coordinate1[0]) + abs(coordinate2[1] - coordinate1[1])


a, b, c = map(int, input().split())
x1, y1, x2, y2 = map(int, input().split())
coor1, coor2 = (x1, y1), (x2, y2)
res = worstCase(coor1, coor2)  # Base Manhattan distance

# If the avenue is not parallel to either axis, compute potential crossing points
if a and b:
    # Compute intersections of the avenue with grid lines through A and B
    range1 = [(x1, (-c - a * x1) / b), ((-c - b * y1) / a, y1)]
    range2 = [(x2, (-c - a * x2) / b), ((-c - b * y2) / a, y2)]
    for upper in range1:
        for lower in range2:
            # Calculate total distance: path to avenue, travel on avenue, path from avenue
            res = min(
                res,
                worstCase(coor1, upper)
                + worstCase(coor2, lower)
                + hypot(upper[0] - lower[0], upper[1] - lower[1]),
            )
print("%.10f" % res)


# https://github.com/VaHiX/codeForces/