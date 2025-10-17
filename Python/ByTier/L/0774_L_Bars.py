# Contest 774, Problem L: Bars
# URL: https://codeforces.com/contest/774/problem/L

from bisect import *


def check(x):
    cur = 0
    kk = k - 1
    while cur + 1 < n:
        prv = cur
        cur = min(n - 1, cur + x)
        while s[cur] == "1":
            cur -= 1
        if prv == cur:
            return False
        kk -= 1
    return kk >= 0


n, k = map(int, input().split())
s = input()
ans = bisect_left(range(1, n), 1, key=lambda x: 1 if check(x) else 0)
print(ans)
