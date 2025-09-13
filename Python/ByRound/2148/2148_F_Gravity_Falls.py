# Contest 2148, Problem F: Gravity Falls
# URL: https://codeforces.com/contest/2148/problem/F

import sys
input=sys.stdin.readline
Q=int(input())
for _ in range(Q):
  N=int(input())
  G=[[] for i in range(N)]
  z=0
  v=[0]*N
  for i in range(N):
    A=list(map(int,input().split()))
    K=A[0]
    A=A[1:]
    G[i]=A[:]
    z=max(z,K)
    v[i]=K
  result=[]
  h=[i for i in range(N)]
  for i in range(z):
    x=10**10
    for pos in h:
      x=min(x,G[pos][i])
    ans=True
    h2=[]
    result.append(x)
    for pos in h:
      if v[pos]==i+1 and G[pos][i]==x:
        ans=False
        break
      if G[pos][i]==x:
        h2.append(pos)
    h=h2[:]
    if ans==False:
      h=[]
      for j in range(N):
        if v[j]>i+1:
          h.append(j)
  print(*result)
    
      
  