# Problem: CF 1933 F - Turtle Mission: Robot and the Earthquake
# https://codeforces.com/contest/1933/problem/F

"""
Algorithm: BFS with state tracking
Time Complexity: O(n * m)
Space Complexity: O(n * m)

The problem models a robot moving on a grid where columns move cyclically upwards over time.
We use BFS to explore the shortest path from (0,0) to (n-1,m-1).
The state includes position (i,j) and time t.
At each step, we can move up, down, or right, but movement depends on the rock positions
which shift cyclically with time.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
from collections import deque

for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [list(map(int, input().split())) for _ in range(n)]
    ans = inf = 1 << 60
    vis = [[0] * m for _ in range(n)]

    # BFS queue stores (row, col, time)
    bfs = deque([(0, 0, 0)])
    vis[0][0] = 1
    while bfs:
        i, j, t = bfs.popleft()
        if j == m - 1:
            # Calculate the minimum time to reach destination (n-1, m-1)
            # considering all possible positions the robot can be in at time t
            ans = t + min((i - t) % n + 1, n - 1 - (i - t) % n)
            break
        # Move right: check for rock at (i+1,j+1) which will be at (i+1,j+1) at time t
        if g[(i + 1) % n][(j + 1) % m] == 0 and not vis[(i + 1) % n][(j + 1) % m]:
            vis[(i + 1) % n][(j + 1) % m] = 1
            bfs += [((i + 1) % n, (j + 1) % m, t + 1)]
        # Move down: check for rock at (i+1,j) and (i+2,j) which will be at (i+1,j) and (i+2,j) at time t
        if g[(i + 1) % n][j] == g[(i + 2) % n][j] == 0 and not vis[(i + 2) % n][j]:
            vis[(i + 2) % n][j] = 1
            bfs += [((i + 2) % n, j, t + 1)]

    print(ans if ans < inf else -1)


# https://github.com/VaHiX/CodeForces/