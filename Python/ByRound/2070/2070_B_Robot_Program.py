# Contest 2070, Problem B: Robot Program
# URL: https://codeforces.com/contest/2070/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, x, k = map(int, input().split())
    s = input()
    p = [0]
    for j in range(n):
        p.append(p[-1] + (1 if s[j] == "R" else -1))
    if not (-x in p) or k < p.index(-x):
        print(0)
    else:
        k -= p.index(-x)
        if 0 in p[1:]:
            ind = p[1:].index(0) + 1
            print(k // ind + 1)
        else:
            print(1)
