# Contest 1444, Problem A: Division
# URL: https://codeforces.com/contest/1444/problem/A

import math
t=int(input())
for _ in range(t):
    p,q=list(map(int,input().split()))
    t=[]
    ans=1
    i=2
    n=q
    while i*i<=n:
        if n%i==0:
            t.append(i)
            n//=i
        else:
            i+=1
    t.append(n)
    #print(t)
    t=set(t)
    for i in t:
        k=p
        #print(i,k,ans)
        while k%q==0:
            k//=i
        #print("k->",k)
        ans=max(ans,k)
    print(ans)