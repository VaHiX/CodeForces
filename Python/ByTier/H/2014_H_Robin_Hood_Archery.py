# Contest 2014, Problem H: Robin Hood Archery
# URL: https://codeforces.com/contest/2014/problem/H

import sys; input=sys.stdin.readline; out=[]
from random import getrandbits
r=[getrandbits(20) for j in range(10**6+1)]
for i in range(int(input())):
  n,q=map(int,input().split())
  a=list(map(int,input().split()))
  p=[0]
  for j in range(n):
    p.append(p[-1]^r[a[j]])
  for j in range(q):
    u,v=map(int,input().split())
    out.append(('no' if p[v]^p[u-1] else 'yes'))
print('\n'.join(out))