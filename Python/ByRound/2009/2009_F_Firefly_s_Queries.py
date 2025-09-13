# Contest 2009, Problem F: Firefly's Queries
# URL: https://codeforces.com/contest/2009/problem/F

import sys; R = sys.stdin.readline
S = lambda: map(int,R().split())
P = print
 
def f(i):
    if i>n: return a[i-n]+a[n]
    return a[i]
for _ in range(int(R())):
    n,q = S()
    a = [0]+[*S()]
    for i in range(n): a[i+1] += a[i]
    for _ in range(q):
        l,r = S()
        x,y = divmod(l-1,n)
        z,w = divmod(r-1,n)
        P(a[n]*(z-x-1)+f(z+w+1)-f(z)-f(x+y)+f(x+n))