# Contest 2040, Problem F: Number of Cubes
# URL: https://codeforces.com/contest/2040/problem/F

from collections import Counter
from itertools import product
M=998244353
fac=[1]
for i in range(1,3*10**6+1):
    fac.append((fac[-1]*i)%M)
def gcd(a,b):
    if b==0: return a
    return gcd(b,a%b)
for _ in range(int(input())):
    a,b,c,k=map(int,input().split())
    D=[int(i) for i in input().split()]
    g=0
    for dk in D:
        g=gcd(g,dk)
    dims=[a,b,c]
    pfs=[Counter() for _ in range(3)]
    pfg=Counter()
    for i in range(3):
        j=2
        while j**2<=dims[i]:
            while dims[i]%j==0:
                pfs[i][j]+=1
                dims[i]//=j
            j+=1
        if dims[i]>1:
            pfs[i][dims[i]]+=1
    tg=g
    j=2
    while j**2<=tg:
        while tg%j==0:
            pfg[j]+=1
            tg//=j
        j+=1
    if tg>1:
        pfg[tg]+=1
    ans=0
    for tpe in product(*([(p,i) for i in range(pfg[p]+1)] for p in pfg)):
        d=1
        for (p,e) in tpe:
            d*=p**e
        num=1
        for (p,e) in tpe:
            T=1
            for i in range(3):
                T*=p**min(pfs[i][p],e)
            S=1
            for i in range(3):
                S*=0 if e==0 else p**min(pfs[i][p],e-1)
            num*=T-S
        den=1
        for dk in D:
            den=(den*fac[dk//d])%M
        ans=(ans+num*fac[(a*b*c)//d]*pow(den,-1,M))%M
    ans=(ans*pow(a*b*c,-1,M))%M
    print(ans)
