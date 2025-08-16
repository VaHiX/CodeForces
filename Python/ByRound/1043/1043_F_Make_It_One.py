# Contest 1043, Problem F: Make It One
# URL: https://codeforces.com/contest/1043/problem/F

from math import gcd
R=3*10**5
def C(n,k):
    if n<k:
        return 0
    y=1
    for i in range(n-k+1,n+1):
        y*=i
    for i in range(2,k+1):
        y//=i
    return y
n=int(input())
c=[0]*(R+1)
for e in input().split():
    c[int(e)]=1
d=[0]*(R+1)
for i in range(1,R+1):
    j=i
    while j<=R:
        d[i]+=c[j]
        j+=i
if gcd(*(i for i in range(1,R+1) if c[i]))>1:
    print(-1)
else:
    k=0
    while 1:
        k+=1
        F=[C(d[i],k) for i in range(R+1)]
        for i in range(R,0,-1):
            j=2*i
            while j<=R:
                F[i]-=F[j]
                j+=i
        if F[1]:
            print(k)
            break