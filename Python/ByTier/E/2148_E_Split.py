# Contest 2148, Problem E: Split
# URL: https://codeforces.com/contest/2148/problem/E

inf = 10000
def inp():return [int(e)for e in input().split()]
    
for ww in range(int(input())):
  n,k=inp()
  a=inp()
  p=[0]*(n+1)
  for e in a:
    p[e]+=1
  if any([e%k for e in p]):
    print(0)
    continue
  l,r=0,-1
  q=[0]*(n+1)
  ans=0
  while r<n-1:
    r+=1
    x = a[r]
    if q[x]==p[x]//k:
      while q[x]==p[x]//k:
        q[a[l]]-=1
        ans+=r-l
        l+=1
      q[x]+=1
      
    else:
      q[a[r]]+=1
  d=r-l+1
  ans+=d*(d+1)//2
  print(ans)
      
    
    
