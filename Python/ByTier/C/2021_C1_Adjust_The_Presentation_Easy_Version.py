# Contest 2021, Problem C1: Adjust The Presentation (Easy Version)
# URL: https://codeforces.com/contest/2021/problem/C1

import sys; input=sys.stdin.readline
for i in range(int(input())):
  n,m,q=map(int,input().split())
  a=list(map(int,input().split()))
  b=list(map(int,input().split()))
  p=0
  s=set()
  check=1
  for j in range(m):
    if (p<n and b[j]==a[p]):
      s.add(a[p])
      p+=1
    elif b[j] in s:
      continue
    else:
      check=0
      break
  print('ya' if check else 'tidak')