# Problem: CF 1749 E - Cactus Wall
# https://codeforces.com/contest/1749/problem/E

import heapq
from sys import stdin


def print_map(i, j, vis, grid):
    # Reconstruct the path from bottom to top using the visited array
    while j != 0:
        grid[i][j] = "#"
        i, j = vis[i][j]
    grid[i][j] = "#"

    for r in grid:
        print("".join(r))


def main():
    # Read grid dimensions
    n, m = map(int, stdin.readline().split())
    grid = [list(stdin.readline().strip()) for i in range(n)]
    # Initialize visited array to track path and cactus placement
    vis = [[()] * m for i in range(n)]

    # Mark adjacent cells to existing cacti as invalid (can't place cacti there)
    for x in range(n):
        for y in range(m):
            if grid[x][y] == "#":
                for dx, dy in ((1, 0), (0, 1), (-1, 0), (0, -1)):
                    xx, yy = x + dx, y + dy
                    if 0 <= xx < n and 0 <= yy < m:
                        vis[xx][yy] = -1

    # Initialize a priority queue (min-heap) with all valid starting points on the left edge
    q = [(1 if grid[i][0] == "." else 0, i, 0) for i in range(n) if vis[i][0] != -1]
    heapq.heapify(q)

    # BFS with priority queue to find a path from top to bottom while minimizing cacti
    while q:
        c, x, y = heapq.heappop(q)
        # If reached the rightmost column, a path exists
        if y == m - 1:
            print("YES")
            print_map(x, y, vis, grid)
            return

        # Travel diagonally (allowed in Minecraft cactus rules)
        for dx, dy in ((-1, -1), (-1, 1), (1, -1), (1, 1)):
            xx, yy = x + dx, y + dy
            if 0 <= xx < n and 0 <= yy < m and not vis[xx][yy]:
                vis[xx][yy] = (x, y)
                # Add cost if the cell is empty (needs cactus)
                heapq.heappush(q, (c + (grid[xx][yy] == "."), xx, yy))

    # No valid path exists to reach the bottom
    print("NO")


# Read number of test cases and process each one
for _ in range(int(stdin.readline())):
    main()

# **Purpose**: This code determines the minimum number of cacti to be planted to block all paths from the top row to the bottom row in a Minecraft-inspired cactus wall problem. It uses BFS with a priority queue to efficiently find such a wall, prioritizing paths that use fewer cacti.

# **Algorithm**:
# 1. Preprocess the grid to mark invalid cells adjacent to existing cacti as `-1`.
# 2. Initialize a priority queue with all valid starting positions (from leftmost column) and their cost (number of cacti needed to block).
# 3. Apply a modified BFS (travelling diagonally) to find the path that minimizes cacti usage to connect top to bottom.
# 4. Reconstruct and print the resulting grid if a solution exists, or report "NO" if it's impossible.

# **Time Complexity**: O(n * m * log(n * m))  
# **Space Complexity**: O(n * m)  
# Where `n` and `m` are the dimensions of the grid. The heap operations contribute a logarithmic factor to the time complexity, and we store visited state and the grid itself.

# https://github.com/VaHiX/CodeForces/