# Problem: CF 1753 D - The Beach
# https://codeforces.com/contest/1753/problem/D

"""
Algorithm: Dijkstra's shortest path with modification
Time Complexity: O(nm * log(nm))
Space Complexity: O(nm)

This solution finds the minimum discomfort to free a space for Andrew's sunbed.
It uses Dijkstra's algorithm to compute the minimum cost to move sunbeds to free cells.
Each cell with a sunbed half (L, R, U, D) can be moved to an adjacent cell,
and the cost depends on whether the movement is a rotation (p) or shift (q).
The algorithm first computes the minimum cost to reach each cell, then
finds the minimum sum of costs for two adjacent free cells.
"""

import heapq
import sys


def solve():
    inp = sys.stdin.readline
    n, m = map(int, inp().split())
    p, q = map(int, inp().split())
    s = [list(inp()) for i in range(n)]

    def getid(x, y):
        return x * m + y

    push = heapq.heappush
    pop = heapq.heappop
    INF = 1 << 62
    D = [INF] * (n * m)
    h = []
    for i in range(n):
        for j in range(m):
            if s[i][j] == ".":
                id = getid(i, j)
                D[id] = 0
                push(h, (0, id))
    while h:
        d, id = pop(h)
        if d != D[id]:
            continue
        x = id // m
        y = id % m
        for xx, yy in (
            (x, y + 1),
            (x, y - 1),
            (x + 1, y),
            (x - 1, y),
        ):
            if xx < 0 or yy < 0 or xx >= n or yy >= m:
                continue
            c = s[xx][yy]
            # Determine where the sunbed half at (xx, yy) will move to
            if c == "U":
                tx, ty = xx + 1, yy
            elif c == "D":
                tx, ty = xx - 1, yy
            elif c == "L":
                tx, ty = xx, yy + 1
            elif c == "R":
                tx, ty = xx, yy - 1
            elif c == "." or c == "#":
                tx, ty = x, y
            else:
                raise Exception("wut")
            if tx == x and ty == y:
                continue
            # Compute cost depending on movement type
            if tx == xx and x == xx or ty == yy and y == yy:
                cost = q  # Shift
            else:
                cost = p  # Rotation
            vid = getid(tx, ty)
            ncost = D[id] + cost
            if D[vid] > ncost:
                D[vid] = ncost
                push(h, (ncost, vid))
    ans = INF
    for i in range(n):
        for j in range(m):
            id = getid(i, j)
            if D[id] != INF:
                if j + 1 < m:
                    vid = getid(i, j + 1)
                    if D[vid] != INF:
                        ans = min(ans, D[id] + D[vid])
                if i + 1 < n:
                    vid = getid(i + 1, j)
                    if D[vid] != INF:
                        ans = min(ans, D[id] + D[vid])
    if ans == INF:
        print(-1)
    else:
        print(ans)


def main():
    solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/