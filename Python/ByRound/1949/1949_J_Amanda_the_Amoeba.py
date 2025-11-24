# Problem: CF 1949 J - Amanda the Amoeba
# https://codeforces.com/contest/1949/problem/J

"""
Algorithm: Amoeba Movement Pathfinding
Techniques: BFS, Dijkstra, Priority Queue (Heap), Graph Traversal

Time Complexity: O(r * c * log(r * c)) where r and c are grid dimensions
Space Complexity: O(r * c) for storing grid states, distances, and queues

This code solves the amoeba movement problem where Amanda needs to move from an initial connected body configuration to a final connected body configuration on a grid.
The solution uses BFS and Dijkstra-like algorithms to find valid paths for moving the amoeba body while maintaining connectivity.
"""

import sys

input = lambda: sys.stdin.readline().strip()

from collections import deque
from heapq import *

n, m = map(int, input().split())
op = []

wall = [[False for _ in range(m)] for i in range(n)]
final = [[False for _ in range(m)] for i in range(n)]
cur = [[False for j in range(m)] for i in range(n)]
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

# Read initial grid configuration
for i in range(n):
    s = input()
    for j in range(m):
        if s[j] == "*":
            cur[i][j] = True
        elif s[j] == "X":
            wall[i][j] = True

input()  # Skip empty line

# Read final grid configuration
for i in range(n):
    s = input()
    for j in range(m):
        if s[j] == "*":
            final[i][j] = True

# Check if any pixel exists in both initial and final positions
Finalposexist = False
for i in range(n):
    for j in range(m):
        if cur[i][j] and final[i][j]:
            Finalposexist = True

# If there's no common pixel, find a path from initial to final using BFS
if not Finalposexist:
    Q = deque()
    d = [[1e18 for i in range(m)] for j in range(n)]
    p = [[[] for j in range(m)] for i in range(n)]

    # Initialize distances from all initial positions
    for i in range(n):
        for j in range(m):
            if cur[i][j]:
                d[i][j] = 0
                Q.append([i, j])

    finalpos = []
    # BFS to find any pixel in final configuration
    while Q:
        i, j = Q.popleft()
        if final[i][j]:
            finalpos = [i, j]
            break

        for k in range(4):
            x = i + dx[k]
            y = j + dy[k]

            if x < 0 or x >= n or y < 0 or y >= m:
                continue
            if d[x][y] <= d[i][j] + 1:
                continue
            if wall[x][y]:
                continue
            if cur[x][y]:
                continue

            d[x][y] = d[i][j] + 1
            p[x][y] = [i, j]
            Q.append([x, y])

    # If no connection found, impossible
    if finalpos == []:
        print("NO")
        exit()

    path = []
    d = [[1e18 for j in range(m)] for i in range(n)]
    d[finalpos[0]][finalpos[1]] = 0

    # Reconstruct path from final to initial
    while not cur[finalpos[0]][finalpos[1]]:
        i, j = finalpos
        path.append([i, j])

        finalpos = p[i][j]
        d[finalpos[0]][finalpos[1]] = d[i][j] + 1

    path = path[::-1]

    Q = deque()
    Q.append(finalpos)

    # Re-calculate distances from final position to all reachable points
    while Q:
        i, j = Q.popleft()

        for k in range(4):
            x = i + dx[k]
            y = j + dy[k]

            if x < 0 or x >= n or y < 0 or y >= m:
                continue
            if d[x][y] <= d[i][j] + 1:
                continue
            if wall[x][y]:
                continue
            if not cur[x][y]:
                continue

            d[x][y] = d[i][j] + 1
            Q.append([x, y])

    # Prepare heap of initial positions with distances
    a = []
    for i in range(n):
        for j in range(m):
            if cur[i][j]:
                heappush(a, [-d[i][j], i, j])

    # Move in the reconstructed path
    for [x, y] in path:
        dd, i, j = heappop(a)

        op.append([i, j, x, y])
        cur[i][j] = False
        cur[x][y] = True
        heappush(a, [-d[x][y], x, y])


# Find the set of final positions that are connected to start points
Q = deque()
d = [[1e18 for j in range(m)] for i in range(n)]
d2 = [[1e18 for j in range(m)] for i in range(n)]
final_component = [[False for j in range(m)] for i in range(n)]

finalpos = []
for i in range(n):
    for j in range(m):
        if cur[i][j] and final[i][j]:
            finalpos = [i, j]
            break
    if finalpos != []:
        break

d[finalpos[0]][finalpos[1]] = 0
d2[finalpos[0]][finalpos[1]] = 0
final_component[finalpos[0]][finalpos[1]] = True
Q.append([finalpos[0], finalpos[1]])

# BFS to find all connected final positions
while Q:
    i, j = Q.popleft()

    for k in range(4):
        x = i + dx[k]
        y = j + dy[k]

        if x < 0 or x >= n or y < 0 or y >= m:
            continue
        if d[x][y] <= d[i][j] + 1:
            continue
        if wall[x][y]:
            continue
        if not final[x][y]:
            continue
        if not cur[x][y]:
            continue

        d[x][y] = d[i][j] + 1
        d2[x][y] = d2[i][j] + 1
        final_component[x][y] = True
        Q.append([x, y])

# Update distances from final component points
for i in range(n):
    for j in range(m):
        if final_component[i][j]:
            Q.append([i, j])

while Q:
    i, j = Q.popleft()

    for k in range(4):
        x = i + dx[k]
        y = j + dy[k]

        if x < 0 or x >= n or y < 0 or y >= m:
            continue
        if d[x][y] <= d[i][j] + 1:
            continue
        if wall[x][y]:
            continue
        if not cur[x][y]:
            continue
        if final_component[x][y]:
            continue

        d[x][y] = d[i][j] + 1
        Q.append([x, y])

# Find all connected positions in the final component
for i in range(n):
    for j in range(m):
        if final_component[i][j]:
            Q.append([i, j])

while Q:
    i, j = Q.popleft()

    for k in range(4):
        x = i + dx[k]
        y = j + dy[k]

        if x < 0 or x >= n or y < 0 or y >= m:
            continue
        if d2[x][y] <= d2[i][j] + 1:
            continue
        if wall[x][y]:
            continue
        if not final[x][y]:
            continue
        if final_component[x][y]:
            continue

        d2[x][y] = d2[i][j] + 1
        Q.append([x, y])


# Prepare heap of initial positions not in final component
a = []
for i in range(n):
    for j in range(m):
        if cur[i][j] and (not final_component[i][j]):
            heappush(a, [-d[i][j], i, j])

# Prepare heap of final component positions
Q = []
for i in range(n):
    for j in range(m):
        if final_component[i][j]:
            heappush(Q, [d2[i][j], i, j])

# Move positions not in final component into it
while Q:
    dd, i, j = heappop(Q)

    for k in range(4):
        x = i + dx[k]
        y = j + dy[k]

        if x < 0 or x >= n or y < 0 or y >= m:
            continue
        if not final[x][y]:
            continue
        if final_component[x][y]:
            continue
        if cur[x][y]:
            final_component[x][y] = True
            heappush(Q, [d2[x][y], x, y])
            continue

        # Find a position to move
        while True:
            dd, u, v = heappop(a)
            if final_component[u][v]:
                continue
            break

        op.append([u, v, x, y])
        cur[u][v] = False
        cur[x][y] = True
        final_component[x][y] = True

        heappush(Q, [d2[x][y], x, y])

# Output result
print("YES")
print(len(op))
for p in op:
    a = [q + 1 for q in p]
    print(*a)


# https://github.com/VaHiX/CodeForces/