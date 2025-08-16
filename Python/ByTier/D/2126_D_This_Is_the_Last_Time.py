# Contest 2126, Problem D: This Is the Last Time
# URL: https://codeforces.com/contest/2126/problem/D

import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n,k = map(int,input().split())
    a = [tuple(map(int,input().split())) for _ in range(n)]
    a.sort(key=lambda x:x[2])
    for l,r,v in a:
        if l <= k <= r:
            k = max(k,v)
    print(k)