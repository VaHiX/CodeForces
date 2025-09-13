# Contest 2005, Problem B2: The Strict Teacher (Hard Version)
# URL: https://codeforces.com/contest/2005/problem/B2

from sys import stdin
input = stdin.readline
import bisect
t = int(input())
for _ in range(t):
    n,m,q = map(int,input().split())
    b = list(map(int,input().split()))
    a = list(map(int,input().split()))
    b = sorted(b)
    for x in a:
        t = bisect.bisect_left(b,x)
        if t==0:
            print(b[0]-1)
        elif t==m:
            print(n-b[-1])
        else:
            print((b[t]-b[t-1])//2)