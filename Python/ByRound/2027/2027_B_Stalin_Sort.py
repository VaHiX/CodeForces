# Contest 2027, Problem B: Stalin Sort
# URL: https://codeforces.com/contest/2027/problem/B

import sys; input=sys.stdin.readline
for i in range(int(input())):
  n=int(input())
  a=list(map(int,input().split()))
  ans=n-1
  for j in range(n):
    cnt=0
    for k in range(j+1,n):
      if a[k]>a[j]:
        cnt+=1
    ans=min(ans,j+cnt)
  print(ans)