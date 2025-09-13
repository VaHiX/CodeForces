# Contest 2148, Problem C: Pacer
# URL: https://codeforces.com/contest/2148/problem/C

import sys
input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n, m = map(int,input().split())
    ans = 0
    l = p = 0
    for _ in range(n):
        a, b = map(int,input().split())
        r = a-l
        if (r&1) ^ (p!=b):
            r -= 1
        ans += r
        l, p = a, b
    print(ans + m-l)