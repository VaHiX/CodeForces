# Problem: CF 1782 A - Parallel Projection
# https://codeforces.com/contest/1782/problem/A

"""
Problem: Minimum cable length between laptop and projector in a rectangular room,
         where cable must follow walls, floor, or ceiling parallel to edges.

Algorithms/Techniques:
- Parallel Projection (manhattan distance on unfolded 2D net of the cuboid)
- Enumerate all possible unfoldings of the cuboid to compute minimal path

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a fixed number of variables

Approach:
The problem reduces to finding the shortest path on the surface of a cuboid.
We can "unfold" the cuboid in different ways and compute Manhattan distance
between the two points. There are 4 possible unfoldings for the path:
    1. From (a, b) to (f, g) via top face
        Path: (a, b) -> (a, 0) -> (0, g) -> (f, g)
        Or similar variations.
    2. From (a, b) to (f, g) via side face(s).

This is solved by unfolding the 3D cuboid into a 2D plane and finding
Euclidean distance between projected points.

The code uses an optimization trick:
    For each of two possible direction choices,
    it evaluates two options by considering how to unfold,
    then selects minimum among those.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    w, d, h = map(int, input().split())  # Room dimensions
    a, b, f, g = map(int, input().split())  # Laptop and projector positions
    
    # Compute minimal path by trying different unfoldings:
    # Option 1: go through floor/wall then ceiling;
    # Option 2: go through ceiling/wall then floor.
    print(
        h
        + min(
            # Option 1: travel along bottom face (floor) with possible side wall
            min(g + b, d - g + d - b) + abs(a - f),
            # Option 2: travel along side walls with ceiling
            min(f + a, w - f + w - a) + abs(b - g),
        )
    )


# https://github.com/VaHiX/codeForces/