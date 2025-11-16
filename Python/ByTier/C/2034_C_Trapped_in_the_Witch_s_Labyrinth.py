# Problem: CF 2034 C - Trapped in the Witch's Labyrinth
# https://codeforces.com/contest/2034/problem/C

"""
C. Trapped in the Witch's Labyrinth

Approach:
This problem involves determining the maximum number of cells from which a path leads to an infinite loop (trap) in a maze.
The maze has directions (U, D, L, R) or unspecified cells marked with '?'. We need to assign directions optimally to maximize the number of trapped cells.

Algorithm:
1. Use BFS to mark all cells that are guaranteed to be "bad" - meaning they eventually lead to an infinite loop or exit.
2. Start BFS with border cells (outside the maze), as these are trivially bad (they lead outside).
3. For each cell, if it points to another valid cell and that cell hasn't been marked as bad yet, mark it as bad.
4. After marking all guaranteed bad positions, count how many unmarked cells would be bad if we try to avoid cycles.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

This solution leverages the idea of identifying "bad" components by reverse propagation from known edge conditions.
"""

import sys
from collections import deque

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


for __ in range(fg()):
    n, m = fgh()
    q = deque()
    bad = [[0] * (m + 2) for i in range(n + 2)]
    # Mark all border cells as bad
    for i in range(n + 2):
        for j in range(m + 2):
            if i == 0 or j == 0 or (n + 1 - i) == 0 or (m + 1 - j) == 0:
                bad[i][j] = 1
                q.append((i, j))
    a = []
    for i in range(n):
        s = input()[:-1]
        a.append(s)
    m1 = [(-1, 0), (0, 1), (0, -1), (1, 0)]  # U, R, L, D
    d = ["U", "R", "L", "D"]
    # BFS to propagate bad cells based on movement rule
    while len(q):
        r, c = q.popleft()
        for i in range(4):
            x, y = r - m1[i][0], c - m1[i][1]
            # Check if the cell pointed by current cell is inside and not already marked bad
            if 0 <= x - 1 < n and 0 <= y - 1 < m and a[x - 1][y - 1] == d[i]:
                if bad[x][y] == 0:
                    q.append((x, y))
                    bad[x][y] = 1
    # Mark remaining cells as bad if they are part of any cycle or unreachable from edge
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            for u in m1:
                # If a neighboring cell is not marked bad, then current cell may be good
                if bad[i - u[0]][j - u[1]] == 0:
                    break
            else:
                # All neighbors are marked bad => current cell is also bad
                bad[i][j] = 1
    # Count remaining unmarked cells which will trap Rostam
    s = 0
    for i in range(n + 2):
        for j in range(m + 2):
            if bad[i][j] == 0:
                s += 1
    print(s)


# https://github.com/VaHiX/codeForces/