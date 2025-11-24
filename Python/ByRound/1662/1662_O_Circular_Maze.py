# Problem: CF 1662 O - Circular Maze
# https://codeforces.com/contest/1662/problem/O

"""
O. Circular Maze

Algorithms/Techniques:
- Graph traversal (BFS)
- Grid representation of circular maze with angle and radius coordinates
- Handling wraparound angles using modulo arithmetic
- Using sets for efficient neighbor lookups

Time Complexity: O(MAX_RADIUS * 360) = O(1) since MAX_RADIUS is fixed at 20
Space Complexity: O(MAX_RADIUS * 360) = O(1) due to fixed dimensions

The problem models a circular maze where we need to find a path from center (radius 0) 
to the outer boundary (radius MAX_RADIUS - 1), avoiding walls. Walls are either:
- Circular: defined by radius and two angles (clockwise arc)
- Straight: defined by angle and radial range

We use BFS traversal over a grid where each cell represents (radius, angle). 
Each cell has up to 4 neighbors (up, right, left, down), with wrapping around 
angles and boundaries checked against wall positions.
"""

from itertools import chain, islice
from sys import stdin

MAX_RADIUS = 20
lines = iter(stdin.readlines()[1:])
for line in lines:
    n = int(line)
    # 2D arrays to mark walls: circular_wall[r][theta] for circular walls,
    # straight_wall[r][theta] for straight walls
    circular_wall, straight_wall = (
        [[False] * 360 for _ in range(MAX_RADIUS)] for _ in range(2)
    )
    for shape, *params in map(str.split, islice(lines, n)):
        params = map(int, params)
        if shape == "C":
            r, theta_1, theta_2 = params
            r -= 1  # Convert to 0-based indexing
            # Handle wraparound angle ranges correctly
            theta_range = (
                range(theta_1, theta_2)
                if theta_1 <= theta_2
                else chain(range(theta_1, 360), range(0, theta_2))
            )
            for theta in theta_range:
                circular_wall[r][theta] = True
        else:
            assert shape == "S"
            r1, r2, theta = params
            r1 -= 1  # Convert to 0-based indexing
            r2 -= 1
            # Mark all radii from r1 to r2-1 at angle theta as walls
            for r in range(r1, r2):
                straight_wall[r][theta] = True
    # Start BFS from all valid positions at radius 0 (center)
    queue = [(0, i) for i, inner_wall in enumerate(circular_wall[0]) if not inner_wall]
    seen = set(queue)
    while queue:
        row, col = queue.pop()
        neighbors = []
        # Check up neighbor (if valid and not a circular wall)
        if row >= 1 and not circular_wall[row][col]:
            neighbors.append((row - 1, col))
        # Right neighbor with wraparound
        right_col = (col + 1) % 360
        if not straight_wall[row][right_col]:
            neighbors.append((row, right_col))
        # Left neighbor with wraparound
        if not straight_wall[row][col]:
            neighbors.append((row, (col - 1) % 360))
        # Down neighbor (if valid and not a circular wall)
        next_row = row + 1
        if not circular_wall[next_row][col]:
            if next_row == MAX_RADIUS - 1:
                print("YES")
                break
            neighbors.append((next_row, col))
        for neighbor in neighbors:
            if neighbor in seen:
                continue
            queue.append(neighbor)
            seen.add(neighbor)
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/