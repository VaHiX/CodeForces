# Contest 2009, Problem E: Klee's SUPER DUPER LARGE Array!!!
# URL: https://codeforces.com/contest/2009/problem/E

import sys
input=sys.stdin.readline

from math import floor,sqrt

f=lambda x: (2*x*x + x*(4*k-2) + (n-n*n-2*k*n))//2

t=int(input())
for _ in range(t):
    n,k=map(int,input().split())
    D=4*k*k + 4*k*(n-1) + (2*n*n-2*n+1)
    i=(floor(sqrt(D))-(2*k-1))//2
    ans=min(abs(f(i)),abs(f(i+1)))
    print(ans)