# Contest 803, Problem A: Maximal Binary Matrix
# URL: https://codeforces.com/contest/803/problem/A

import sys
n,k=[int(i) for i in input().split()]
s=[n*['0'] for i in range(n)]
if(k>n*n):
    print(-1)
    sys.exit()
heng=0
zong=0
while(k>0):
    if(heng==zong):
        k-=1
        s[heng][zong]='1'
        
    elif(heng!=zong and k!=1):
        k-=2
        s[heng][zong]='1'
        s[zong][heng]='1'
    zong+=1
    if(zong==n):
        heng+=1
        zong=heng
for i in range(n):
    h=str(s[i])
    print(' '.join(s[i]))