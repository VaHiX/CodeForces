# Contest 889, Problem A: Petya and Catacombs
# URL: https://codeforces.com/contest/889/problem/A

import sys
readline=sys.stdin.readline

N=int(readline())
T=list(map(int,readline().split()))
ans=N+1-len(set(T))
print(ans)