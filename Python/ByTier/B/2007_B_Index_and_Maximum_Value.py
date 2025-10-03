# Contest 2007, Problem B: Index and Maximum Value
# URL: https://codeforces.com/contest/2007/problem/B

import sys; input=sys.stdin.readline
for i in range(int(input())):
  n,m=map(int,input().split())
  a=list(map(int,input().split()))
  maxo=max(a)
  out=[]
  for j in range(m):
    c,l,r=input().split()
    l,r=int(l),int(r)
    if l<=maxo<=r:maxo+=1-2*int(c=='-')
    out.append(maxo)
  print(*out)