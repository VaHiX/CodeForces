# Contest 2094, Problem F: Trulimero Trulicina
# URL: https://codeforces.com/contest/2094/problem/F

import sys

input = lambda: sys.stdin.readline()

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    idx = 0
    for i in range(n):
        for j in range(m):
            if m % k:
                print((i * m + j) % k + 1, end=" ")
            else:
                print((i * m + j + idx) % k + 1, end=" ")
        idx += 1

        print()
