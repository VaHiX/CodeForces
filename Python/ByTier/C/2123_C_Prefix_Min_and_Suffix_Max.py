# Contest 2123, Problem C: Prefix Min and Suffix Max
# URL: https://codeforces.com/contest/2123/problem/C

import sys
input = sys.stdin.readline
t=int(input())
for _ in range(t):
  n=int(input())
  a=list(map(int,input().split()))
  ans=["0"]*n
  ans[0]="1"
  ans[-1]="1"
  mi=a[0]
  for i in range(1,n):
    if a[i]<mi:
      ans[i]="1"
      mi=a[i]
  ma=a[-1]
  for i in range(n-2,-1,-1):
    if a[i]>ma:
      ans[i]="1"
      ma=a[i]
  print("".join(ans))