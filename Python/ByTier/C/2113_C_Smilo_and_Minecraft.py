# Contest 2113, Problem C: Smilo and Minecraft
# URL: https://codeforces.com/contest/2113/problem/C

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n, m, k = map(int, input().split())
    g = (
        [["#"] * (2 * k + m) for _ in range(k)]
        + [["#"] * k + [i for i in input()] + ["#"] * k for _ in range(n)]
        + [["#"] * (2 * k + m) for _ in range(k)]
    )
    n += 2 * k
    m += 2 * k
    c = 0
    for i in range(n):
        for j in range(m):
            c += 1 if g[i][j] == "g" else 0
    d = [[0] * m for _ in range(n)]
    for i in range(1, n):
        h = 0
        for j in range(m):
            if g[i][j] == "g":
                h += 1
            d[i][j] = d[i - 1][j] + h
    x = c
    for i in range(k, n - k):
        for j in range(k, m - k):
            if g[i][j] == ".":
                x = min(
                    x,
                    d[i + k - 1][j + k - 1]
                    + d[i - k][j - k]
                    - d[i - k][j + k - 1]
                    - d[i + k - 1][j - k],
                )
    print(c - x)
