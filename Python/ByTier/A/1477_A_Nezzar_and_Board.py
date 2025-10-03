# Contest 1477, Problem A: Nezzar and Board
# URL: https://codeforces.com/contest/1477/problem/A

import sys
import math

input = sys.stdin.readline
for ___ in range(int(input())):
    n, k = [int(xx) for xx in input().split()]
    a = [int(Ss) for Ss in input().split()]
    a = sorted(a)
    r = []
    for i in range(1, n):
        r.append(a[i] - a[i - 1])
    ee = 0
    for i in range(n - 1):
        ee = math.gcd(ee, r[i])
    if (k - a[0]) % ee:
        print("NO")
    else:
        print("YES")
