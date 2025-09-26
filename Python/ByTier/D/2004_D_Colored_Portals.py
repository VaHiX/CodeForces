# Contest 2004, Problem D: Colored Portals
# URL: https://codeforces.com/contest/2004/problem/D

import sys,io,os
try:Z=io.BytesIO(os.read(0,os.fstat(0).st_size)).readline
except:Z=lambda:sys.stdin.readline().encode()
Y=lambda:map(int,Z().split())
O=[]
arr=[b'BG',b'BR',b'BY',b'GR',b'GY',b'RY']
d=dict((arr[i],i)for i in range(6))
for _ in range(*Y()):
    n,q=Y();a=[d[s]for s in Z().split()];L=[-1]*n;R=[-1]*n;B=[-1]*6
    for i in range(n):
        L[i]=max(B[j]for j in range(6)if j!=a[i]and j!=5-a[i]);B[a[i]]=i
    B=[n]*6
    for i in range(n-1,-1,-1):
        R[i]=min(B[j]for j in range(6)if j!=a[i]and j!=5-a[i]);B[a[i]]=i
    for i in range(q):
        x,y=sorted(Y());x-=1;y-=1
        if a[x]!=5-a[y]or R[x]<y:O.append(y-x);continue
        v1=v2=3*n
        if R[y]<n:v1=2*R[y]-y-x
        if L[x]>=0:v2=y+x-2*L[x]
        if v2<v1:v1=v2
        if v1<3*n:O.append(v1);continue
        O.append(-1)
print('\n'.join(map(str,O)))