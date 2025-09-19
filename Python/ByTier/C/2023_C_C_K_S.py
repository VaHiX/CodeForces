# Contest 2023, Problem C: C+K+S
# URL: https://codeforces.com/contest/2023/problem/C

from sys import stdin
input=lambda :stdin.readline()[:-1]


def z_algo(S):
    N = len(S)
    A = [0]*N
    i = 1; j = 0
    A[0] = l = len(S)
    while i < l:
        while i+j < l and S[j] == S[i+j]:
            j += 1
        if not j:
            i += 1
            continue
        A[i] = j
        k = 1
        while l-i > k < j - A[k]:
            A[i+k] = A[k]
            k += 1
        i += k; j -= k
    return A
  
def f(n,k,edge):
  seen=[-1]*n
  seen[0]=0
  todo=[0]
  while todo:
    v=todo.pop()
    for u in edge[v]:
      if seen[u]==-1:
        seen[u]=(seen[v]+1)%k
        todo.append(u)
  return seen


def g(n,X,Y):
  z=z_algo(X+Y+Y)
  ok=[0]*n
  for i in range(n):
    if z[i+n]>=n:
      ok[i]=1
  return ok

def solve():
  n,k=map(int,input().split())
  a1=list(map(int,input().split()))
  edge1=[[] for i in range(n)]
  m1=int(input())
  for _ in range(m1):
    x,y=map(lambda x:int(x)-1,input().split())
    edge1[x].append(y)
    
    
  a2=list(map(int,input().split()))
  m2=int(input())
  edge2=[[] for i in range(n)]
  for _ in range(m2):
    x,y=map(lambda x:int(x)-1,input().split())
    edge2[x].append(y)


  if sum(a1)+sum(a2)!=n:
    print("NO")
    return
  if sum(a1)==n or sum(a2)==n:
    print("YES")
    return
  
  col1=f(n,k,edge1)
  col2=f(n,k,edge2)
  
  v1=[0]*k
  v2=[0]*k
  
  for i in range(n):
    if a1[i]==0:
      v1[col1[i]-2]+=n+1
    else:
      v1[col1[i]]+=1
    if a2[i]==0:
      v2[col2[i]]+=1
    else:
      v2[col2[i]]+=n+1
      
  print("YES" if k in z_algo(v1+[-1]+v2*2) else "NO")

for _ in range(int(input())):
  solve()