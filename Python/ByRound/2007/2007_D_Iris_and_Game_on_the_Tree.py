# Contest 2007, Problem D: Iris and Game on the Tree
# URL: https://codeforces.com/contest/2007/problem/D

from sys import stdin
input = stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    deg = [0]*(n+1)
    for i in range(n-1):
        u,v = map(int,input().split())
        deg[u] += 1
        deg[v] += 1
    x,y,z,w = 0,0,0,0
    s = ' '+input()
    for i  in range(2,n+1):
        if deg[i]==1:
            if s[i]=='0':
                x += 1
            elif s[i]=='1':
                y += 1
            else:
                z += 1
        elif s[i]=='?':
            w += 1
    if s[1]=='0':
        print(y+(z+1)//2)
    elif s[1]=='1':
        print(x+(z+1)//2)
    else:
        print(max(x,y)+(z+(w%2 if x==y else 0))//2)


