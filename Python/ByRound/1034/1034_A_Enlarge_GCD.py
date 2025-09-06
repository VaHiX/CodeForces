# Contest 1034, Problem A: Enlarge GCD
# URL: https://codeforces.com/contest/1034/problem/A

import math

def sieve():
    n = 15000002
    spf = [i for i in range(n+1)]
    for i in range(4,n,2):
        spf[i] = 2
    for i in range(3,n):
        if i*i>n:
            break
        if spf[i]==i:
            for j in range(2*i,n,i):
                if spf[j]==j:
                    spf[j] = i
    return spf
        
spf=sieve()
#print(spf[:20])
n=int(input())
a=list(map(int,input().split()))

g=math.gcd(a[0],a[1])

for i in range(2,n):
    g=math.gcd(g,a[i])
flag=False
for i in range(n):
    a[i]=a[i]//g
    if a[i]>1:
        flag=True
if flag==False:
    print(-1)
else:
    ans=-1
    f=[0]*(max(a)+1)

    for i in range(len(a)):
        num = a[i]
        while(num>1):
            p = spf[num]
            f[p]+=1
            num = num//p
            ans = max(ans, f[p])
            while(num%p == 0):
                num = num//p
                
    #print(f,n,ans,max(f))
    print(n-ans)
  