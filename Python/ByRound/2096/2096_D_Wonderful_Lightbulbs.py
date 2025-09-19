# Contest 2096, Problem D: Wonderful Lightbulbs
# URL: https://codeforces.com/contest/2096/problem/D

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    s = 0
    c = 0
    for _ in range(n):
        x, y = map(int, input().split())
        s ^= x
        c ^= x + y
    print(s, c - s)
