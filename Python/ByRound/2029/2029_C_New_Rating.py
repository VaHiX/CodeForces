# Contest 2029, Problem C: New Rating
# URL: https://codeforces.com/contest/2029/problem/C

import sys

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)


def f(x, v):
    return x + (v > x) - (v < x)


def main():
    n = int(input())
    (*a,) = map(int, input().split())
    x, y, z = 0, -n, -n
    for v in a:
        x, y, z = f(x, v), max(x, y), max(f(z, v), f(y, v))
    print(max(y, z))


tcs = int(input())
for tc in range(tcs):
    main()
