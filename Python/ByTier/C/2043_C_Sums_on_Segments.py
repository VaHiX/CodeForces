# Contest 2043, Problem C: Sums on Segments
# URL: https://codeforces.com/contest/2043/problem/C

from sys import stdin

inp = stdin.readline

t = int(inp())

for _ in range(t):
    n = int(inp())
    arr = [int(x) for x in inp().split()]

    m = [[0, 0], [0, 0]]
    f = 0
    d = [0, 0]
    nr = 0

    cnt = 0
    for c in arr:
        if c == 1 or c == -1:
            cnt += c
            d[0] = max(cnt - m[f][0], d[0])
            d[1] = max(m[f][1] - cnt, d[1])
            m[f][0] = min(cnt, m[f][0])
            m[f][1] = max(cnt, m[f][1])
        else:
            m[0][0] -= cnt
            m[0][1] -= cnt
            cnt = 0
            f = 1
            nr = c

    s = set(range(-d[1], d[0] + 1))

    if f:
        s = s.union(
            set(
                range(
                    min(-m[0][0] + nr + m[1][1], -m[0][1] + nr + m[1][0]),
                    max(-m[0][0] + nr + m[1][1], -m[0][1] + nr + m[1][0]) + 1,
                )
            )
        )

    print(len(s))
    print(*sorted(list(s)))
