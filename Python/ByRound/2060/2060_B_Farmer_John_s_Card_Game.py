# Contest 2060, Problem B: Farmer John's Card Game
# URL: https://codeforces.com/contest/2060/problem/B

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, m = map(int, input().split())
    a = []
    for i in range(n):
        b = map(int, input().split())
        for x in b:
            a.append((x, i))

    a.sort()
    b = [i[1] for i in a[:n]]

    if [i[1] for i in a] == b * m:
        print(*[i + 1 for i in b])
    else:
        print(-1)
