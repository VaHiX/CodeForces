# Contest 2117, Problem D: Retaliation
# URL: https://codeforces.com/contest/2117/problem/D

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    x = (n * a[-1] - a[0]) // (n * n - 1)
    y = a[-1] - x * n
    if (n * a[-1] - a[0]) % (n * n - 1) == 0 and min(x, y) >= 0:
        f = 1
        for j in range(n):
            f &= int(a[j] == x * (j + 1) + y * (n - j))
        print("YES" if f else "NO")
    else:
        print("NO")
