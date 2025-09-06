# Contest 2133, Problem D: Chicken Jockey
# URL: https://codeforces.com/contest/2133/problem/D

import sys; input=sys.stdin.readline
for i in range(int(input())):
  n=int(input())
  a=list(map(int,input().split()))
  dp=[(0 if j!=1 else a[0]) for j in range(n+1)]
  for j in range(1,n):
    dp[j+1]=min(dp[j]+a[j]-1,dp[j-1]+a[j-1]+max(0,a[j]-j))
  print(dp[-1])