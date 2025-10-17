# Contest 2005, Problem D: Alter the GCD
# URL: https://codeforces.com/contest/2005/problem/D

import sys
input = sys.stdin.readline
t=int(input())
import math
for _ in range(t):
  n=int(input())
  a=list(map(int,input().split()))
  b=list(map(int,input().split()))
  dp=[set(),set(),set()]
  dp[0].add((a[0],b[0]))
  dp[1].add((b[0],a[0]))
  for i in range(1,n):
    dp2=[set(),set(),set()]
    for x,y in dp[0]:
      g1=math.gcd(x,a[i])
      g2=math.gcd(y,b[i])
      dp2[0].add((g1,g2))
      g1=math.gcd(x,b[i])
      g2=math.gcd(y,a[i])
      dp2[1].add((g1,g2))
    for x,y in dp[1]:
      g1=math.gcd(x,a[i])
      g2=math.gcd(y,b[i])
      dp2[2].add((g1,g2))
      g1=math.gcd(x,b[i])
      g2=math.gcd(y,a[i])
      dp2[1].add((g1,g2))   
    for x,y in dp[2]:
      g1=math.gcd(x,a[i])
      g2=math.gcd(y,b[i])
      dp2[2].add((g1,g2))
    dp=dp2
  ma=0
  for x,y in dp[1]:
    ma=max(ma,x+y)
  for x,y in dp[2]:
    ma=max(ma,x+y)
  l=set()
  for x,y in dp[1]:
    if ma==x+y:
      l.add((x,y))
  for x,y in dp[2]:
    if ma==x+y:
      l.add((x,y))
  ans=0
  for x,y in l:
    memo=[]
    for i in range(n):
      if a[i]%x>0 or b[i]%y>0:
        memo.append(1)
      elif a[i]%y>0 or b[i]%x>0:
        memo.append(-1)
      else:
        memo.append(0)
    if 1 not in memo:
      cnt=0
      for i in memo:
        if i==0:
          cnt+=1
        else:
          ans+=(cnt*(cnt+1))//2
          cnt=0
      ans+=(cnt*(cnt+1))//2
    else:
      for i in range(n):
        if memo[i]==1:
          left=i
          break
      for i in range(n-1,-1,-1):
        if memo[i]==1:
          right=i
          break
      left2=-1
      for i in range(left-1,-1,-1):
        if memo[i]!=0:
          left2=i
          break
      right2=n
      for i in range(right+1,n):
        if memo[i]!=0:
          right2=i
          break
      ans+=(left-left2)*(right2-right)
  print(ma,ans)