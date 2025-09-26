# Contest 2084, Problem B: MIN = GCD
# URL: https://codeforces.com/contest/2084/problem/B

from math import gcd
import sys

input = lambda: sys.stdin.readline().strip()

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    g = 0
    for x in a[1:]:
        if x % a[0] != 0:
            continue
        g = gcd(g, x)
    if g == a[0]:
        print("Yes")
    else:
        print("No")
