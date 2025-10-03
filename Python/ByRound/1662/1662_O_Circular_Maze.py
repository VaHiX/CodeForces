# Contest 1662, Problem O: Circular Maze
# URL: https://codeforces.com/contest/1662/problem/O

from itertools import islice, chain
from sys import stdin

MAX_RADIUS = 20

lines = iter(stdin.readlines()[1:])

for line in lines:
    n = int(line)
    circular_wall, straight_wall = (
        [[False] * 360 for _ in range(MAX_RADIUS)] for _ in range(2)
    )
    for shape, *params in map(str.split, islice(lines, n)):
        params = map(int, params)
        if shape == "C":
            r, theta_1, theta_2 = params
            r -= 1
            theta_range = (
                range(theta_1, theta_2)
                if theta_1 <= theta_2
                else chain(range(theta_1, 360), range(0, theta_2))
            )
            for theta in theta_range:
                circular_wall[r][theta] = True
        else:
            assert shape == "S"
            r1, r2, theta = params
            r1 -= 1
            r2 -= 1
            for r in range(r1, r2):
                straight_wall[r][theta] = True

    queue = [(0, i) for i, inner_wall in enumerate(circular_wall[0]) if not inner_wall]
    seen = set(queue)
    while queue:
        row, col = queue.pop()
        # print(row, col)
        neighbors = []
        if row >= 1 and not circular_wall[row][col]:
            neighbors.append((row - 1, col))
        right_col = (col + 1) % 360
        if not straight_wall[row][right_col]:
            neighbors.append((row, right_col))
        if not straight_wall[row][col]:
            neighbors.append((row, (col - 1) % 360))
        next_row = row + 1
        if not circular_wall[next_row][col]:
            if next_row == MAX_RADIUS - 1:
                print("YES")
                break
            neighbors.append((next_row, col))

        for neighbor in neighbors:
            if neighbor in seen:
                continue
            queue.append(neighbor)
            seen.add(neighbor)
    else:  # no break
        print("NO")
