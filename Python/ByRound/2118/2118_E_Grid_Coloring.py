# Contest 2118, Problem E: Grid Coloring
# URL: https://codeforces.com/contest/2118/problem/E

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = [int(x) for x in input().split()]
    cx, cy = (n + 1) // 2, (m + 1) // 2
    coords = [(x, y) for x in range(1, n + 1) for y in range(1, m + 1)]
    coords.sort(
        key=lambda pos: (
            max(abs(pos[0] - cx), abs(pos[1] - cy)),
            abs(pos[0] - cx) + abs(pos[1] - cy),
        )
    )
    print("\n".join(f"{x} {y}" for x, y in coords))
