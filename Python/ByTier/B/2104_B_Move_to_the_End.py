# Contest 2104, Problem B: Move to the End
# URL: https://codeforces.com/contest/2104/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [0]
    for j in range(n):
        b.append(max(b[-1], a[j]))
    out = []
    cur = 0
    for j in range(n - 1, -1, -1):
        cur += a[j]
        out.append(cur + max(0, b[j] - a[j]))
    print(*out)
