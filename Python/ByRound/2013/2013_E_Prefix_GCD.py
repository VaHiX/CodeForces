# Contest 2013, Problem E: Prefix GCD
# URL: https://codeforces.com/contest/2013/problem/E

import sys
input = sys.stdin.readline
from math import gcd

def solve():
    n = int(input())
    a = list(map(int, input().split()))
    g = 0
    for x in a: g = gcd(g, x)

    for i in range(n):
        a[i] //= g
    
    ans = 0
    cur = 0
    for i in range(n):
        mn = 1e9
        for j in range(n):
            mn = min(mn, gcd(cur, a[j]))
        
        cur = mn

        ans += cur
        if cur == 1:
            ans += n - i - 1
            break
    print(ans * g)

for _ in range(int(input())):
    solve()