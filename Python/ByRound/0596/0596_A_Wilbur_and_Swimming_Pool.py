# Contest 596, Problem A: Wilbur and Swimming Pool
# URL: https://codeforces.com/contest/596/problem/A

import math

def rl():
    return map(int,input().split())

def ri():
    return int(input())

n=ri()

x=[]
y=[]

while n:
    a,b=rl()
    x.append(a)
    y.append(b)
    n-=1

s=(max(x)-min(x))*(max(y)-min(y))

if s==0:
    print(-1)
else:
    print(s)