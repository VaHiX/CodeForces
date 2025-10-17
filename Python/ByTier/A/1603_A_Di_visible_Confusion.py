# Contest 1603, Problem A: Di-visible Confusion
# URL: https://codeforces.com/contest/1603/problem/A

import sys

input = sys.stdin.buffer.readline
from math import gcd


def lcm(x, y):
    return x * y // gcd(x, y)


f = [2]
for i in range(30):
    if f[-1] > 10**9:
        break
    f.append(lcm(f[-1], i + 3))
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ok = True
    for i in range(min(n, len(f))):
        if a[i] % f[i] == 0:
            ok = False
    print("YES" if ok else "NO")
