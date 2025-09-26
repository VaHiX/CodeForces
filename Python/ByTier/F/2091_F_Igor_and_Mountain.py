# Contest 2091, Problem F: Igor and Mountain
# URL: https://codeforces.com/contest/2091/problem/F

import sys
from math import isqrt

input = sys.stdin.readline

MOD = 998244353

for _ in range(int(input())):
    gy, gx, d = map(int, input().split())
    diag = isqrt(d * d - 1)
    grid = [input() for _ in range(gy)]

    def step(curr_row, ways, dist):
        psa = [0]
        for num in ways:
            psa.append((psa[-1] + num) % MOD)

        for x in range(gx):
            ways[x] = (
                curr_row[x] == "X"
                and (psa[min(gx, x + dist + 1)] - psa[max(0, x - dist)]) % MOD
            )

    ways = [int(c == "X") for c in grid[-1]]
    step(grid[-1], ways, d)

    for y in range(gy - 2, -1, -1):
        step(grid[y], ways, diag)
        step(grid[y], ways, d)

    total = 0
    for num in ways:
        total = (total + num) % MOD
    print(total)
