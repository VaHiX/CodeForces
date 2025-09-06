# Contest 1394, Problem A: Boboniu Chats with Du
# URL: https://codeforces.com/contest/1394/problem/A

import sys
input = lambda: sys.stdin.readline().rstrip()

N,D,M = map(int, input().split())
A = list(map(int, input().split()))

a1,a2=[],[]
for a in A:
    if a>M:
        a2.append(a)
    else:
        a1.append(a)
a1.sort(reverse=True)
a2.sort(reverse=True)

dp = [0]*(N+1)
for i in range(N):
    if i<len(a1):
        dp[i+1] = dp[i]+a1[i]
    else:
        dp[i+1] = dp[i]
#print(dp)

ans,cur=dp[-1],0
for i in range(len(a2)):
    cur+=a2[i]
    t = N-(i*(D+1)+1)
    if t<0:break
    ans = max(ans, cur+dp[t])
print(ans)
    