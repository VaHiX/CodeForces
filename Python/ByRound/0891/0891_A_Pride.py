# Contest 891, Problem A: Pride
# URL: https://codeforces.com/contest/891/problem/A

import math
n=int(input())
a=list(map(int,input().split()))
ans,cnt=n,a.count(1)
for i in range(n):
  m=a[i]
  for j in range(i+1,n):
    m=math.gcd(m,a[j])
    if m==1: ans=min(ans,j-i-1)
if cnt>0: print(n-cnt)
elif ans==n: print(-1)
else: print(n+ans)