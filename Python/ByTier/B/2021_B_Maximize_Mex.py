# Contest 2021, Problem B: Maximize Mex
# URL: https://codeforces.com/contest/2021/problem/B

import heapq as hq
import sys
input=sys.stdin.readline
F=lambda:[*map(int,input().split())]

for _ in range(int(input())):
  N,X=F()
  A=F()
  CNT=[0]*(N+2)
  for a in A:
    if a<=N:CNT[a]+=1
  for i in range(N+2):
    if CNT[i]==0:print(i);break
    if CNT[i]>1 and i+X<N+2:
      CNT[i+X]+=CNT[i]-1