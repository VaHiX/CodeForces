# Contest 2013, Problem D: Minimize the Difference
# URL: https://codeforces.com/contest/2013/problem/D

import sys
input = sys.stdin.readline

t = int(input())
o = []
for _ in range(t):
  n = int(input())
  a = list(map(int, input().split()))
  
  lo = 10 ** 15
  hi = 0
  tl = tr = 0
  for i in range(n):
      tl += a[i]
      tr += a[~i]
      
      lo = min(lo, tl//(i+1))
      hi = max(hi, (tr+i)//(i+1))
  o.append(hi-lo)
print('\n'.join(map(str, o)))