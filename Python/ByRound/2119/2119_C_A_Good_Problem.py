# Contest 2119, Problem C: A Good Problem
# URL: https://codeforces.com/contest/2119/problem/C

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, l, r, k = map(int, input().split())
    if n & 1:
        print(l)
        continue
    if n == 2:
        print(-1)
        continue
    x = 1 << l.bit_length()
    if x > r:
        print(-1)
    else:
        print(l if k <= n - 2 else x)
