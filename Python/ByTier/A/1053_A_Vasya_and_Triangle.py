# Contest 1053, Problem A: Vasya and Triangle
# URL: https://codeforces.com/contest/1053/problem/A

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################
n,m,k =  na()

if (n * m * 2) % k:
    print("NO")
    exit()
from math import gcd
gn = gcd(n,k)
N = n // gn
k //= gn

gm = gcd(m,k)
M = m // gm
k //= gm

if k == 1:
    if N * 2 <= n:
        N *= 2
    else:
        M *= 2
    

print("YES")
print(0,0)
print(N,0)
print(0,M)
