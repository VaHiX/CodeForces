# Contest 2131, Problem C: Make it Equal
# URL: https://codeforces.com/contest/2131/problem/C

def inp():return [int(e)for e in input().split()]
def f(e):return str(e)
for _ in range(int(input())):
  n,k=inp()
  a=inp()
  b=inp()
  f=[]
  for e in a:
    f+=[min(e%k,k-e%k)]
  g=[]
  for e in  b:
    g+=[min(e%k,k-e%k)]
  if sorted(f)==sorted(g):print('YES')
  else:print('NO')
