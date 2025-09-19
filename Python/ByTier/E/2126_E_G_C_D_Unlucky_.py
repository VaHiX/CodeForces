# Contest 2126, Problem E: G-C-D, Unlucky!
# URL: https://codeforces.com/contest/2126/problem/E

import sys
from math import gcd

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    s = list(map(int, input().split()))
    if p[-1] != s[0]:
        print("NO")
        continue
    flg = False
    for i in range(n - 1):
        if gcd(p[i], s[i + 1]) != s[0] or p[i] % p[i + 1] > 0 or s[i + 1] % s[i] > 0:
            print("NO")
            break
    else:
        print("YES")
