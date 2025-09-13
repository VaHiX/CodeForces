# Contest 2121, Problem C: Those Who Are With Us
# URL: https://codeforces.com/contest/2121/problem/C

import sys

input = sys.stdin.readline


def solve():
    n, m = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(n)]

    mx = max([max(x) for x in grid])
    count = sum([grid[i].count(mx) for i in range(n)])

    rows = [0 for _ in range(n)]
    cols = [0 for _ in range(m)]

    for i in range(n):
        for j in range(m):
            if grid[i][j] == mx:
                rows[i] += 1
                cols[j] += 1

    for i in range(n):
        for j in range(m):
            if rows[i] + cols[j] - (grid[i][j] == mx) == count:
                return mx - 1

    return mx


for _ in range(int(input())):
    print(solve())
