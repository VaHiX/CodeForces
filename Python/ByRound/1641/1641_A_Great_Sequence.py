# Contest 1641, Problem A: Great Sequence
# URL: https://codeforces.com/contest/1641/problem/A

import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n,x=list(map(int, input().split()))
    a=list(map(int, input().split()))

    d={}
    a.sort()
    c=0

    for el in a:
        if el not in d:
            d[el]=1
        else:
            d[el]+=1

    for z in d:
        if z*x in d:
            p,q= d[z], d[z*x]
            c+=min(p,q)
            d[z]-=min(p,q)
            d[z*x]-=min(p,q)
            
    print(n-(c*2))