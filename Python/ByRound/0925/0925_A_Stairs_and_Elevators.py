# Contest 925, Problem A: Stairs and Elevators
# URL: https://codeforces.com/contest/925/problem/A

import sys
from bisect import bisect_left
from math import ceil

input = sys.stdin.readline
n, m, cl, ce, v = map(int, input().split())
l = list(map(int, input().split()))
e = list(map(int, input().split()))
q = int(input())
for _ in range(q):
    x1, y1, x2, y2 = map(int, input().split())
    if x1 == x2:
        print(abs(y1 - y2))
        continue
    ans = []
    idx = bisect_left(l, y1)
    for i in range(idx - 1, idx + 2):
        if 0 <= i < cl:
            t = abs(y1 - l[i]) + abs(x1 - x2) + abs(l[i] - y2)
            ans.append(t)
    idx = bisect_left(e, y1)
    for i in range(idx - 1, idx + 2):
        if 0 <= i < ce:
            t = abs(y1 - e[i]) + ceil(abs(x1 - x2) / v) + abs(y2 - e[i])
            ans.append(t)
    print(min(ans))
