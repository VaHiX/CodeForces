# Contest 2072, Problem D: For Wizards, the Exam Is Easy, but I Couldn't Handle It
# URL: https://codeforces.com/contest/2072/problem/D

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    ma = 0
    ans = (1, 1)
    for i in range(n):
        now = 0
        for j in range(i + 1, n):
            if a[i] > a[j]:
                now += 1
            elif a[i] < a[j]:
                now -= 1
            if ma < now:
                ma = now
                ans = (i + 1, j + 1)
    print(*ans)
