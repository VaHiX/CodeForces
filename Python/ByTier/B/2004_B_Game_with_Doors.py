# Contest 2004, Problem B: Game with Doors
# URL: https://codeforces.com/contest/2004/problem/B

import sys; input=sys.stdin.readline
for i in range(int(input())):
  l,r=map(int,input().split())
  a,b=map(int,input().split())
  if r<a or b<l:
    print(1)
  else:
    print(min(r,b)+int(r!=b)-max(l,a)+int(a!=l))