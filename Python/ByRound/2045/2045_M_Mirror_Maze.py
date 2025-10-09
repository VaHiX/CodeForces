# Problem: CF 2045 M - Mirror Maze
# https://codeforces.com/contest/2045/problem/M

"""
M. Mirror Maze
Algorithms/Techniques: Simulation with reflection tracking
Time Complexity: O(R * C * (R + C)) - For each direction and starting point, simulate beam path
Space Complexity: O(R * C) - To store the grid and visited mirrors

The problem involves a grid with mirrors that reflect light beams. 
We need to find all valid laser entry points such that all mirrors are hit.
For each of the 2*(R+C) possible entry locations, we simulate a beam path,
tracking which mirrors are visited until the beam exits the grid.
If all mirrors are visited in one simulation, that entry point is valid.
"""

n, m = map(int, input().split())  # Read grid dimensions
a, d = [input() for i in range(n)], []  # Read grid and list to store valid directions

# Count total number of mirrors in the grid
k = n * m - sum(i.count(".") for i in a)

# For each of the four directions (N, E, S, W)
for i in "NESW":
    for j in range(n if i in "NS" else m):  # Adjust range depending on direction
        b = set()  # Set to track visited mirrors
        x, y, dx, dy = {
            "N": (j, 0, 0, 1),    # Start at column j, row 0, moving south (dy=1)
            "E": (m - 1, j, -1, 0), # Start at col m-1, row j, moving west (dx=-1)
            "S": (j, n - 1, 0, -1), # Start at column j, row n-1, moving north (dy=-1)
            "W": (0, j, 1, 0),    # Start at col 0, row j, moving east (dx=1)
        }[i]

        # Simulate beam until it exits the grid or loops
        while 0 <= x < m and 0 <= y < n:
            if a[y][x] in "/\\":  # Hit a mirror
                # Update direction based on mirror type
                dx, dy = [(-dy, -dx), (dy, dx)][a[y][x] != "/"]
                b.add((x, y))  # Mark this mirror as hit
            x += dx  # Move beam
            y += dy

        if len(b) == k:  # All mirrors were hit
            d += [f"{i}{j+1}"]  # Store valid start point

print(len(d))  # Print number of valid lasers
if d:
    print(*d, sep=" ")  # Print valid laser locations


# https://github.com/VaHiX/codeForces/