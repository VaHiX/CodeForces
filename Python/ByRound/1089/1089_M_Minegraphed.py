# Problem: CF 1089 M - Minegraphed
# https://codeforces.com/contest/1089/problem/M

"""
Code Purpose:
This code designs a 3D game field that models the reachability of a given directed graph.
It constructs a 3D grid where each vertex of the graph corresponds to a labeled position in the grid.
The movement rules in the game ensure that valid moves in the grid correspond exactly to edges in the graph.
The solution uses a specific layout construction to achieve this mapping.

Algorithms/Techniques:
- Grid construction with specific layout for each vertex
- Direct mapping of graph edges to grid paths using strategic obstacle placement
- Layered 3D grid representation with top-bottom, north-south, and west-east dimensions

Time Complexity: O(n^2) where n is the number of vertices
Space Complexity: O(n^2) for storing the grid and graph representation

The algorithm works by:
1. Creating a 3D grid with dimensions 3*n x 3*n x 3
2. For each vertex i, placing it in the bottom layer with coordinates (3*i+1, 3*i+1)
3. For each edge from i to j, creating paths between these vertices using obstacles
4. Using a specific pattern of obstacles and empty cells to ensure proper movement behavior
"""

import os
import sys

import random
from io import BytesIO, IOBase
import math

input = lambda: sys.stdin.readline().strip()

inf = math.inf

def I():
    return input()

def II():
    return int(input())

def MII():
    return map(int, input().split())

def LI():
    return input().split()

def LII():
    return list(map(int, input().split()))

def LFI():
    return list(map(float, input().split()))

def GMI():
    return map(lambda x: int(x) - 1, input().split())

def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))

BUFSIZE = 4096

fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y

class lst_lst:
    def __init__(self, n) -> None:
        self.n = n
        self.pre = []
        self.cur = []
        self.notest = [-1] * (n + 1)

    def append(self, i, j):
        self.pre.append(self.notest[i])
        self.notest[i] = len(self.cur)
        self.cur.append(j)

    def iterate(self, i):
        tmp = self.notest[i]
        while tmp != -1:
            yield self.cur[tmp]
            tmp = self.pre[tmp]


n = II()
grid = [LII() for _ in range(n)]

ans = [[[-1] * (3 * n) for _ in range(3 * n)] for _ in range(3)]

for i in range(n):
    idx = 3 * i + 1

    # Set boundaries of the grid (creating empty spaces)
    for j in range(3 * n):
        ans[0][idx][j] = 0  # Top layer
        ans[2][j][idx] = 0  # Bottom layer
    ans[2][-1][idx] = i + 1  # Label position on bottom layer

    # Create the position marker with obstacles to control movement
    ans[1][idx - 1][idx] = 0  # Empty space
    ans[1][idx - 1][idx - 1] = 0  # Empty space
    ans[0][idx - 1][idx - 1] = 0  # Empty space

    # Set connections based on graph edges
    for j in range(n):
        if grid[i][j]:
            jdx = 3 * j + 1
            ans[0][idx - 1][jdx] = 0  # Empty space for connection
            ans[1][idx - 1][jdx] = 0  # Empty space for connection
            ans[2][idx - 1][jdx] = 0  # Empty space for connection

print(3 * n, 3 * n, 3)
for i in range(3):
    if i:
        print()
    print(
        "\n".join("".join(str(x) if x > 0 else "#."[x + 1] for x in y) for y in ans[i])
    )


# https://github.com/VaHiX/CodeForces/