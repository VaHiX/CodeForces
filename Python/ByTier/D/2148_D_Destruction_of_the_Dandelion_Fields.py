# Contest 2148, Problem D: Destruction of the Dandelion Fields
# URL: https://codeforces.com/contest/2148/problem/D

import sys; input=sys.stdin.readline
for i in range(int(input())):
  n=int(input())
  a=list(map(int,input().split()))
  ans=0
  b=[]
  for j in range(n):
    if a[j]%2:
      b.append(a[j])
    else:
      ans+=a[j]
  if not(b):
    print(0)
  else:
    b.sort(reverse=True)
    ans+=sum(b[:len(b)//2+len(b)%2])
    print(ans)