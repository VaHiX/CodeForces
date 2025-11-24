# Problem: CF 1613 E - Crazy Robot
# https://codeforces.com/contest/1613/problem/E

"""
Algorithm/Techniques: BFS, Graph Traversal

Time Complexity: O(n * m) where n is number of rows and m is number of columns.
Space Complexity: O(n * m) for storing the grid and the queue.

This code determines which free cells in a grid can guarantee the robot will reach the lab.
The robot is "crazy" - it will avoid the command direction and move in any other valid direction.
The algorithm uses BFS starting from the lab and works backward to find cells from which
the robot can be forced to move towards the lab regardless of its choices.

The key idea is:
1. Start BFS from the lab position.
2. At each step, check if a cell is reachable by checking if it has at most one free neighbor
   and there's at least one cell in the set of reachable cells (marked + or L) among its neighbors.
3. A cell can be controlled if it leads to a single path toward the lab.
"""

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n, m = map(int, input().split())
    MAP = [input().strip() for i in range(n)]
    ANS = [["."] * m for i in range(n)]

    for i in range(n):
        for j in range(m):

            if MAP[i][j] == "L":
                LAB = (i, j)

            if MAP[i][j] != ".":
                ANS[i][j] = MAP[i][j]
                continue

    Q = [LAB]

    while Q:
        i, j = Q.pop()

        for x, y in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]:
            if 0 <= x < n and 0 <= y < m and ANS[x][y] == ".":
                count = 0
                flag = 0
                for z, w in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
                    if 0 <= z < n and 0 <= w < m and ANS[z][w] == ".":
                        count += 1
                    if (
                        0 <= z < n
                        and 0 <= w < m
                        and (ANS[z][w] == "+" or ANS[z][w] == "L")
                    ):
                        flag = 1
                if count <= 1 and flag == 1:
                    ANS[x][y] = "+"
                    Q.append((x, y))

    for i in range(n):
        print("".join(ANS[i]))


# https://github.com/VaHiX/CodeForces/