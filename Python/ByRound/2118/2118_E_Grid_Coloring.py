# Problem: CF 2118 E - Grid Coloring
# https://codeforces.com/contest/2118/problem/E

"""
E. Grid Coloring

Purpose:
This code finds a coloring order for an n×m grid (where n and m are odd) such that no cell receives more than 3 penalties.
Penalties are assigned based on distance from previously colored cells using chessboard distance (max(|x1-x2|, |y1-y2|)) with Manhattan distance as a tie-breaker.

Algorithm:
The strategy involves sorting all grid coordinates by their "distance" from the center of the grid (cx, cy).
Cells are ordered such that:
1. First by maximum of absolute differences (chessboard distance)
2. Then by sum of absolute differences (Manhattan distance) to break ties

This greedy approach ensures that cells farther from the current coloring point are considered earlier,
which helps in limiting penalty accumulation.

Time Complexity: O(nm * log(nm))
Space Complexity: O(nm)

Note: The sorting step dominates time complexity; all other operations are linear.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = [int(x) for x in input().split()]
    cx, cy = (n + 1) // 2, (m + 1) // 2  # Center of the grid
    coords = [(x, y) for x in range(1, n + 1) for y in range(1, m + 1)]  # All coordinates
    # Sort by chessboard distance from center, then Manhattan distance as tie-breaker
    coords.sort(
        key=lambda pos: (
            max(abs(pos[0] - cx), abs(pos[1] - cy)),  # Chessboard distance
            abs(pos[0] - cx) + abs(pos[1] - cy),       # Manhattan distance
        )
    )
    print("\n".join(f"{x} {y}" for x, y in coords))  # Output the sorted coordinates


# https://github.com/VaHiX/codeForces/