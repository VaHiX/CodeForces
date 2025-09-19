# Contest 2018, Problem B: Speedbreaker
# URL: https://codeforces.com/contest/2018/problem/B

import sys

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print("\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs)

def main():
    n = int(input())
    *a, = map(int, input().split())
    mn = [-1] * n
    mx = [-1] * n
    for i, x in enumerate(a):
        x -= 1
        if mn[x] == -1:
            mn[x] = i
        mx[x] = i
    lo = 0
    hi = n-1
    l = n
    r = -1
    for i, (x, y) in enumerate(zip(mn, mx)):
        if x == -1: continue
        d = i - (y - x)
        l = min(l, x)
        r = max(r, y)
        if d < 0 or i < r - l:
            print(0)
            return
        lo = max(lo, x - d)
        hi = min(hi, y + d)
    print(max(hi - lo + 1, 0))

tcs = int(input())
for tc in range(tcs):
    main()
