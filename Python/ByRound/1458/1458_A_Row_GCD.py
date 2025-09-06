# Contest 1458, Problem A: Row GCD
# URL: https://codeforces.com/contest/1458/problem/A

import sys
input = sys.stdin.buffer.readline
a,b=map(int, input().split())
import math
c=list(map(int, input().split()))
d=list(map(int, input().split()))
s=max(c)
c=[s-i for i in c]
h=0
for i in c:
    h=math.gcd(h,i)
for i in d:
    print(math.gcd(h,s+i),end=" ")