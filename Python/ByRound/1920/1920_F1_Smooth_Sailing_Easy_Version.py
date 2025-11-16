# Problem: CF 1920 F1 - Smooth Sailing (Easy Version)
# https://codeforces.com/contest/1920/problem/F1

"""
Algorithm: 
- Preprocess the grid to compute the minimum Manhattan distance from each cell to the nearest underwater volcano using BFS.
- For each query, use binary search on the answer combined with a validation check:
  - Validation uses BFS to see if it's possible to go around the island such that all cells have distance >= mid from any volcano.
  - The validation process:
    1. First BFS: Starting from the query cell, mark all cells with distance >= mid from any volcano (excluding islands).
    2. Second BFS: From the island center, do a BFS to check if we can reach the border without crossing a valid round trip, which means we fully encircle the island.
- Time Complexity: O(n * m * log(n * m)) - Preprocessing BFS takes O(n * m), and for each query, binary search + BFS takes O(n * m * log(n * m)).
- Space Complexity: O(n * m) - For storing distances, visited arrays, and queues.
"""

from collections import deque


def solve():
    n, m, q = map(int, input().split())
    Dx = [-1, 0, 1, 0, -1, -1, 1, 1]
    Dy = [0, 1, 0, -1, -1, 1, 1, -1]

    d = [[1e9] * m for _ in range(n)]
    v = [list(input()) for _ in range(n)]
    dq = deque()

    for i in range(n):
        for j in range(m):
            if v[i][j] == "v":
                d[i][j] = 0
                dq.append((i, j))
            elif v[i][j] == "#":
                x0, y0 = i, j

    # Preprocessing: compute distance to nearest volcano
    while dq:
        i, j = dq.popleft()
        for k in range(4):
            i1, j1 = i + Dx[k], j + Dy[k]
            if 0 <= i1 < n and 0 <= j1 < m and d[i1][j1] == 1e9:
                d[i1][j1] = d[i][j] + 1
                dq.append((i1, j1))

    for _ in range(q):
        x, y = map(int, input().split())
        x -= 1
        y -= 1
        l, r = 0, d[x][y]

        def check(md):
            vs = [[False] * m for _ in range(n)]
            dq = deque([(x, y)])
            vs[x][y] = True

            # First BFS: mark valid cells based on distance to volcano
            while dq:
                i, j = dq.popleft()
                for k in range(4):
                    i1, j1 = i + Dx[k], j + Dy[k]
                    if (
                        0 <= i1 < n
                        and 0 <= j1 < m
                        and d[i1][j1] >= md
                        and not vs[i1][j1]
                        and v[i1][j1] != "#"
                    ):
                        vs[i1][j1] = True
                        dq.append((i1, j1))

            # Second BFS: check if we can cross the island to borders
            dq.clear()
            dq.append((x0, y0))
            vs[x0][y0] = True

            while dq:
                i, j = dq.popleft()
                if not i or not j or i == n - 1 or j == m - 1:
                    return False
                for k in range(8):
                    i1, j1 = i + Dx[k], j + Dy[k]
                    if vs[i1][j1]:
                        continue
                    vs[i1][j1] = True
                    dq.append((i1, j1))
            return True

        # Binary search on the answer
        while l < r:
            md = (l + r) // 2
            if check(md + 1):
                l = md + 1
            else:
                r = md

        print(l)


if __name__ == "__main__":
    t = 1

    while t > 0:
        solve()
        t -= 1


# https://github.com/VaHiX/CodeForces/