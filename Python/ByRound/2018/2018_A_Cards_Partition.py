# Contest 2018, Problem A: Cards Partition
# URL: https://codeforces.com/contest/2018/problem/A

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    x, y = max(w), sum(w)
    for i in range(n, 0, -1):
        a = (y + k) // i
        if a * i >= y and a >= x:
            print(i)
            break
