# Contest 2059, Problem C: Customer Service
# URL: https://codeforces.com/contest/2059/problem/C

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = [list(map(int, input().split())) for _ in range(n)]
    for i in range(n):
        a[i].reverse()
    # print(a)
    a.sort()
    # print(a)
    i = n - 2
    j = 0
    while i >= 0 and j < n:
        if a[i][j] == 1:
            j += 1
        i -= 1
    print(j + 1)
