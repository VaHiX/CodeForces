# Contest 2051, Problem E: Best Price
# URL: https://codeforces.com/contest/2051/problem/E

import sys

input = sys.stdin.readline
from bisect import bisect_left


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort()
    b.sort()
    vals = [*a, *b]
    vals.sort()

    ans = 0
    l = 0
    r = 0
    for c in vals:
        while l < n and b[l] < c:
            l += 1
        while r < n and a[r] < c:
            r += 1
        cnt = r - l
        if cnt > k:
            continue
        ans = max(ans, c * (n - l))

    print(ans)


for _ in range(int(input())):
    solve()
