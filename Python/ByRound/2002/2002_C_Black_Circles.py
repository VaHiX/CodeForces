# Contest 2002, Problem C: Black Circles
# URL: https://codeforces.com/contest/2002/problem/C

import sys
input=sys.stdin.readline
for _ in range(int(input())):
    n=int(input())
    l=[]
    for i in range(n):
        a,b=map(int,input().split())
        l.append([a,b])
    xs,ys,xf,yf=map(int,input().split())
    ans='YES'
    for i in range(n):
        ai,bi=l[i]
        if((xf-ai)**2+(yf-bi)**2<=(xs-xf)**2+(ys-yf)**2):ans='NO';break
    print(ans)