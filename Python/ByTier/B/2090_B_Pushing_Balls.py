# Problem: CF 2090 B - Pushing Balls
# https://codeforces.com/contest/2090/problem/B

"""
B. Pushing Balls

Purpose:
This code determines whether a given final state of an n x m grid can be achieved by pushing balls into the grid from the left or top edges, following specific rules about ball movement and collisions.

Algorithms/Techniques:
- Simulation-based validation using logical checks for each cell in the grid.
- For each cell (i,j) that has a ball (value 1), we check if it's possible to reach that state based on prior rows/columns being empty.

Time Complexity:
O(n * m) per test case. We iterate through all cells once, performing constant-time operations for each.

Space Complexity:
O(n * m) for storing the grid input.

Rules:
- A ball pushed from left edge of row i will move right until it finds an occupied position.
- A ball pushed from top edge of column j will move down until it finds an occupied position.
- If a row or column is fully filled, no more balls can be pushed into it.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [list(map(int, input())) for _ in range(n)]
    ans = "YES"
    # Iterate over all cells starting from (1,1) to check if they can be reached
    for i in range(1, n):
        for j in range(1, m):
            if g[i][j]:  # If there is a ball at current position
                # Check if any cell to the left in same row is empty
                # And any cell above in same column is empty
                # If both are true, then this ball cannot be placed without violating rules
                if any(g[i][k] == 0 for k in range(j)) and any(
                    g[k][j] == 0 for k in range(i)
                ):
                    ans = "NO"
    print(ans)


# https://github.com/VaHiX/codeForces/