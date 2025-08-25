# Contest 1782, Problem A: Parallel Projection
# URL: https://codeforces.com/contest/1782/problem/A

import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    w, d, h = map(int, input().split())
    a, b, f, g = map(int, input().split())
    print(
        h
        + min(
            min(g + b, d - g + d - b) + abs(a - f),
            min(f + a, w - f + w - a) + abs(b - g),
        )
    )
