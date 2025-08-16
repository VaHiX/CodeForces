# Contest 2123, Problem G: Modular Sorting
# URL: https://codeforces.com/contest/2123/problem/G

import math

def get_factors(n):
    factors = set()
    for i in range(1, int(math.isqrt(n)) + 1):
        if n % i == 0:
            factors.add(i)
            factors.add(n // i)
    return sorted(factors)

for _ in range(int(input())):
    n,m,q=map(int,input().split())
    l=list(map(int,input().split()))
    t=get_factors(m)
    t.pop()
    d=[]
    c=0
    for i in range(n):
        d.append(l[i]-c)
        c=l[i]
    g=[]
    l=[0]+l
    for i in range(len(t)):
        s=0
        for j in range(n):
            s+=(d[j]%t[i])
        g.append([t[i],s])
    #print(g)
    for i in range(q):
        r=list(map(int,input().split()))
        if r[0]==1:
            for j in range(len(t)):
                if r[1]!=n:
                    a=l[r[1]]-l[r[1]-1]
                    b=l[r[1]+1]-l[r[1]]
                    c=r[2]-l[r[1]-1]
                    d=l[r[1]+1]-r[2]
                    #print(a,b,c,d,g[j][1])
                    g[j][1]=g[j][1]-(a%t[j])-(b%t[j])+(c%t[j])+(d%t[j])
                    #print(g[j][1])
                else:
                    a=l[r[1]]-l[r[1]-1]
                    c=r[2]-l[r[1]-1]
                    g[j][1]=g[j][1]-(a%t[j])+(c%t[j])
            l[r[1]]=r[2]
            #print(g)
        else:
            #print(g)
            for j in range(len(g)):
                if g[j][0]==math.gcd(m,r[1]):
                    if g[j][1]>=m:
                        print("NO")
                    else:
                        print("YES")
                    break