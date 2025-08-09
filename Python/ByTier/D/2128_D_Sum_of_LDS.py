# Contest 2128, Problem D: Sum of LDS
# URL: https://codeforces.com/contest/2128/problem/D

t=int(input())
for _ in range(t):
    n=int(input())
    p=list(map(int,input().split()))
    dp=[0]*(n+1)
    dp[n-1]=1
    for i in range(n-2,-1,-1):
        if p[i]>p[i+1]:
            dp[i]=dp[i+1]+n-i
        else:
            dp[i]=dp[i+2]+n-i
    print(sum(dp))