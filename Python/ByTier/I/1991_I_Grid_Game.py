# Contest 1991, Problem I: Grid Game
# URL: https://codeforces.com/contest/1991/problem/I

from random import *
from sys import *


def can_place_domino(grid, x, y, orientation):
    rows, cols = len(grid), len(grid[0])
    if orientation == "horizontal":
        return y + 1 < cols and grid[x][y] == 0 and grid[x][y + 1] == 0
    elif orientation == "vertical":
        return x + 1 < rows and grid[x][y] == 0 and grid[x + 1][y] == 0


def place_domino(grid, x, y, orientation, value):
    if orientation == "horizontal":
        grid[x][y] = value
        grid[x][y + 1] = value
        cells.add(((x, y), (x, y + 1)))
    elif orientation == "vertical":
        grid[x][y] = value
        grid[x + 1][y] = value
        cells.add(((x, y), (x + 1, y)))


def remove_domino(grid, x, y, orientation):
    place_domino(grid, x, y, orientation, 0)
    if orientation == "horizontal":
        cells.remove(((x, y), (x, y + 1)))
    elif orientation == "vertical":
        cells.remove(((x, y), (x + 1, y)))


def assert1(b):
    if not b:
        while 1:
            pass


domcount = 0


def solve(grid):
    global domcount
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            if grid[x][y] == 0:
                for orientation in ["horizontal", "vertical"]:
                    if can_place_domino(grid, x, y, orientation):
                        place_domino(grid, x, y, orientation, domcount + 8)
                        domcount += 1
                        if solve(grid):
                            return True
                        domcount -= 1
                        remove_domino(grid, x, y, orientation)
                return False
    return True


def print_grid(grid):
    for row in grid:
        print(" ".join(str(cell) for cell in row), flush=8)
        stdout.flush()
        stdout.flush()
        stdout.flush()
        stdout.flush()
        stdout.flush()
        stdout.flush()
        stdout.flush()
        stdout.flush()


debug = 0


def query():
    if not debug:
        s = input()
        if s == "-1":
            assert1(false)
        return map(int, s.split())
    while 1:
        x, y = randint(1, n), randint(1, m)
        x -= 1
        y -= 1
        while (sum(sum(j) for j in visited)) > 0 and (
            not (
                x > 0
                and visited[x - 1][y]
                or x < n - 1
                and visited[x + 1][y]
                or y > 0
                and visited[x][y - 1]
                or y < m - 1
                and visited[x][y + 1]
            )
        ):
            x, y = randint(0, n - 1), randint(0, m - 1)
        x += 1
        y += 1
        if not visited[x - 1][y - 1]:
            print("opponent", x, y, values[x - 1][y - 1])
            return x, y


if debug:
    ttt = 100
else:
    ttt = int(input())
G = [[1, 2, 2, 2], [1, 1, 2, 3], [1, 8, 3, 3], [9, 8, 4, 3], [9, 4, 4, 4]]
for tautautautautauooooooooooooooooooooo in range(ttt):
    domcount = 0
    cells = set()
    if debug:
        n, m = 7, 6
    else:
        n, m = map(int, input().split())
    # if (n,m)==(6,9):
    #    while 1: pass
    visited = [[0 for a in range(m)] for b in range(n)]
    grid = [[0 for a in range(m)] for b in range(n)]
    if n * m % 2 == 1:
        grid[-1][-1] = 1
        solve(grid)
        cellmap = {}
        for i in cells:
            cellmap[i[0]] = i[1]
            cellmap[i[1]] = i[0]
        values = [[0 for a in range(m)] for b in range(n)]
        for i in range(n):
            for j in range(m):
                values[i][j] = i * m + j + 1
        print_grid(values)
        their_sum = 0
        our_sum = 0
        for i in range(n * m):
            if i % 2 == 0:
                r, c = query()
                r -= 1
                c -= 1
                visited[r][c] = 1
                their_sum += values[r][c]
            if i % 2 == 1:
                do = (-1, -1)
                for x in range(n):
                    for y in range(m):
                        if (
                            visited[x][y] == 0
                            and visited[cellmap[(x, y)][0]][cellmap[(x, y)][1]] == 1
                        ):
                            do = (x, y)
                            break
                    if do != (-1, -1):
                        break
                if do != (-1, -1):
                    our_sum += values[do[0]][do[1]]
                    print(
                        do[0] + 1,
                        do[1] + 1,
                        ("" if not debug else values[do[0]][do[1]]),
                        flush=8,
                    )
                    stdout.flush()
                    visited[do[0]][do[1]] = 1
                    continue
                do = (-1, -1)
                for x in range(n):
                    for y in range(m):
                        if visited[x][y] == 0 and (
                            (
                                x > 0
                                and visited[x - 1][y]
                                or x < n - 1
                                and visited[x + 1][y]
                                or y > 0
                                and visited[x][y - 1]
                                or y < m - 1
                                and visited[x][y + 1]
                            )
                        ):
                            do = (x, y)
                            break
                assert1(do != (-1, -1))
                print(
                    do[0] + 1,
                    do[1] + 1,
                    ("" if not debug else values[do[0]][do[1]]),
                    flush=8,
                )
                stdout.flush()
                our_sum += values[do[0]][do[1]]
                visited[do[0]][do[1]] = 1
        assert1(our_sum < their_sum)
    else:

        if n % 2 == 0 and m % 2 == 0 or n % 2 == 1 and m % 2 == 0:
            jambloat1 = [
                [(0, 2), (0, 1), (0, 3), (1, 2)],
                [(1, 0), (0, 0), (1, 1), (2, 0)],
            ]
        elif n % 2 == 0 and m % 2 == 1:
            jambloat1 = [
                [(0, 1), (0, 0), (0, 2), (1, 1)],
                [(2, 0), (1, 0), (2, 1), (3, 0)],
            ]
        # elif n%2==1 and m%2==0:
        #    jambloat1 = [[(0,1),(0,0),(0,2),(1,1)],[(2,0),(1,0),(2,1),(3,0)]]
        #    jambloated_regions = [[(k[1],k[0]) for k in j] for j in jambloated_regions]
        jambloated_regions = jambloat1[:]
        for bloat in jambloat1:
            l1 = bloat[:]
            l1 = [(n - i - 1, m - j - 1) for i, j in l1]
            jambloated_regions.append(l1)
        if n == 5 and m == 4:
            jambloated_regions = [
                [(1, 0), (1, 1), (0, 0), (2, 0)],
                [(0, 2), (0, 3), (0, 1), (1, 2)],
                [(2, 3), (2, 2), (3, 3), (1, 3)],
                [(4, 2), (4, 1), (4, 3), (3, 2)],
            ]
        if n == 4 and m == 5:
            jambloated_regions = [
                [(1, 0), (1, 1), (0, 0), (2, 0)],
                [(0, 2), (0, 3), (0, 1), (1, 2)],
                [(2, 3), (2, 2), (3, 3), (1, 3)],
                [(4, 2), (4, 1), (4, 3), (3, 2)],
            ]
            jambloated_regions = [[(k[1], k[0]) for k in j] for j in jambloated_regions]
        if n == 6 and m == 5:
            jambloated_regions = [
                [(1, 0), (1, 1), (0, 0), (2, 0)],
                [(0, 2), (0, 3), (0, 1), (1, 2)],
                [(1, 4), (1, 3), (2, 4), (0, 4)],
                [(5, 3), (5, 2), (5, 4), (4, 3)],
            ]
        if n == 5 and m == 6:
            jambloated_regions = [
                [(1, 0), (1, 1), (0, 0), (2, 0)],
                [(0, 2), (0, 3), (0, 1), (1, 2)],
                [(1, 4), (1, 3), (2, 4), (0, 4)],
                [(5, 3), (5, 2), (5, 4), (4, 3)],
            ]
            jambloated_regions = [[(k[1], k[0]) for k in j] for j in jambloated_regions]

        for i in range(4):
            for j in jambloated_regions[i]:
                grid[j[0]][j[1]] = i + 1

        solve(grid)
        if n == 5 and m == 4:
            assert1(grid == G)
        cellmap = {}
        for i in cells:
            cellmap[i[0]] = i[1]
            cellmap[i[1]] = i[0]
        values = [[0 for a in range(m)] for b in range(n)]
        sv = {i for i in range(1, n * m + 1)}
        leader_vals = [1, 2, 3, 4]
        sub_vals = [n * m + i for i in range(-11, 1)]
        for i in range(4):
            values[jambloated_regions[i][0][0]][jambloated_regions[i][0][1]] = (
                leader_vals[i]
            )
            for j in range(1, 4):
                values[jambloated_regions[i][j][0]][jambloated_regions[i][j][1]] = (
                    sub_vals[3 * i + j - 1]
                )
        remvals = list(range(5, min(sub_vals)))
        pointer = 0
        for i in cells:
            values[i[0][0]][i[0][1]] = remvals[pointer]
            pointer += 1
            values[i[1][0]][i[1][1]] = remvals[pointer]
            pointer += 1
        print_grid(values)
        their_sum = 0
        our_sum = 0
        for op in range(n * m):
            if op % 2 == 0:
                r, c = query()
                r -= 1
                c -= 1
                visited[r][c] = 1
                their_sum += values[r][c]
            if op % 2 == 1:
                do = (-1, -1)

                for i in range(4):
                    if (
                        not visited[jambloated_regions[i][0][0]][
                            jambloated_regions[i][0][1]
                        ]
                    ) and any(
                        visited[jambloated_regions[i][j][0]][
                            jambloated_regions[i][j][1]
                        ]
                        for j in range(1, 4)
                    ):
                        do = jambloated_regions[i][0]
                        break
                if do != (-1, -1):
                    print(
                        do[0] + 1,
                        do[1] + 1,
                        ("" if not debug else values[do[0]][do[1]]),
                        flush=8,
                    )
                    stdout.flush()
                    our_sum += values[do[0]][do[1]]
                    visited[do[0]][do[1]] = 1
                    continue
                for i in range(4):
                    if (
                        visited[jambloated_regions[i][0][0]][
                            jambloated_regions[i][0][1]
                        ]
                    ) and (
                        not any(
                            visited[jambloated_regions[i][j][0]][
                                jambloated_regions[i][j][1]
                            ]
                            for j in range(1, 4)
                        )
                    ):
                        do = jambloated_regions[i][1]
                        break

                for i in range(4):
                    sup = 0
                    for j in range(4):
                        sup += visited[jambloated_regions[i][j][0]][
                            jambloated_regions[i][j][1]
                        ]
                    if sup == 3:
                        for j in range(4):
                            if not visited[jambloated_regions[i][j][0]][
                                jambloated_regions[i][j][1]
                            ]:
                                do = jambloated_regions[i][j]
                        break
                if do != (-1, -1):
                    print(
                        do[0] + 1,
                        do[1] + 1,
                        ("" if not debug else values[do[0]][do[1]]),
                        flush=8,
                    )
                    stdout.flush()
                    our_sum += values[do[0]][do[1]]
                    visited[do[0]][do[1]] = 1
                    continue
                for i in range(n):
                    for j in range(m):
                        if (
                            (i, j) in cellmap
                            and visited[i][j] == 0
                            and visited[cellmap[(i, j)][0]][cellmap[(i, j)][1]] == 1
                        ):
                            do = (i, j)

                assert1(do != (-1, -1))
                print(
                    do[0] + 1,
                    do[1] + 1,
                    ("" if not debug else values[do[0]][do[1]]),
                    flush=8,
                )
                our_sum += values[do[0]][do[1]]
                visited[do[0]][do[1]] = 1

        assert1(our_sum < their_sum)
