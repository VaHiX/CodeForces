# Contest 1548, Problem A: Web of Lies
# URL: https://codeforces.com/contest/1548/problem/A

import sys, io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
print = sys.stdout.write

n, m = list(map(int, input().split()))
ls = [0]*(n+1) #prvo manji, pa veci
res = 0

for i in range(m):
    a, b = sorted(list(map(int, input().split())))
    ls[a] = ls[a]+1

for i in range(1, n+1):
    if ls[i]==0:
        res = res+1

q = int(input())
for i in range(q):
    x = input().decode()
    if x[0]=="3":
        print(str(res)+"\n")
        continue
    
    c, a, b = list(map(int, x.split()))
    if a>b:
        a, b = b,a
    
    if c==1:
        ls[a] = ls[a]+1
        if ls[a]==1:
            res = res-1
    elif c==2:
        ls[a] = ls[a]-1
        if ls[a]==0:
            res = res+1