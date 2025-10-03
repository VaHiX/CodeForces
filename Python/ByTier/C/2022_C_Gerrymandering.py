# Contest 2022, Problem C: Gerrymandering
# URL: https://codeforces.com/contest/2022/problem/C

from sys import stdin
input = stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    vot = [[0]*(n+5) for _ in range(2)]
    for i in range(2):
        tmp = input()
        for j in range(n):
            if tmp[j]=='A':
                vot[i][j+1] = 1
    dp = [[-1]*3 for _ in range(n+5)]
    dp[0][0] = 0
    for k in range(n):
        for i in range(3):
            if dp[k][i]!=-1:
                val = dp[k][i]
                if i==0:
                    vt = (vot[0][k+1]+vot[0][k+2]+vot[0][k+3])//2+(vot[1][k+1]+vot[1][k+2]+vot[1][k+3])//2
                    dp[k+3][0] = max(dp[k+3][0],val+vt)
                    vt = (vot[0][k+1]+vot[0][k+2]+vot[1][k+1])//2
                    dp[k+1][1] = max(dp[k+1][1],val+vt)
                    vt = (vot[1][k+1]+vot[1][k+2]+vot[0][k+1])//2
                    dp[k+1][2] = max(dp[k+1][2],val+vt)
                elif i==1:
                    vt = (vot[0][k+2]+vot[0][k+3]+vot[0][k+4])//2+(vot[1][k+1]+vot[1][k+2]+vot[1][k+3])//2
                    dp[k+3][1] = max(dp[k+3][1],val+vt)
                    vt = (vot[1][k+1]+vot[1][k+2]+vot[0][k+2])//2
                    dp[k+2][0] = max(dp[k+2][0],val+vt)
                elif i==2:
                    vt = (vot[0][k+1]+vot[0][k+2]+vot[0][k+3])//2+(vot[1][k+2]+vot[1][k+3]+vot[1][k+4])//2
                    dp[k+3][2] = max(dp[k+3][2],val+vt)
                    vt = (vot[0][k+1]+vot[0][k+2]+vot[1][k+2])//2
                    dp[k+2][0] = max(dp[k+2][0],val+vt)
    print(dp[n][0])



