# Contest 2004, Problem G: Substring Compression
# URL: https://codeforces.com/contest/2004/problem/G

import sys
def input():return sys.stdin.readline().rstrip()
n,k = map(int,input().split(' '))
a = list(map(int,input()))
ans = [int(1e9)] * (n-k+1)
for l in range(0,n-k+1,k+1):
    mid = l+k-1
    r = min(n-1,mid+k)
    for boss in range(0,10):
        dp1 = [[int(1e9)]*(r-mid+1) for i in range(10)]
        dp1[boss][0] = 0
        for i in range(mid+1,r+1):
            new0 = int(1e9)
            for j in range(1,10):
                new0 = min(new0,dp1[j][i-mid-1] + j)
                dp1[j][i-mid] = dp1[j][i-mid-1] + j
            dp1[a[i]][i-mid] = min(dp1[int(a[i])][i-mid], dp1[0][i-mid-1])
            dp1[0][i-mid] = new0
        dp2 = [[int(1e9)]*(mid-l+2) for i in range(10)]
        dp2[boss][0] = 0
        for i in range(mid,l-1,-1):
            new0 = int(1e9)
            for j in range(1,10):
                dp2[j][mid-i+1] = min(dp2[j][mid-i], dp2[0][mid-i]) + j
                if a[i] == j:
                    new0 = min(new0, dp2[j][mid-i])
            dp2[0][mid-i+1] = new0
        for i in range(l,l+k+1):
            cur_l = i
            cur_r = i+k-1
            if cur_r >= n:
                break
            ans[i] = min(ans[i],dp2[0][mid-cur_l+1]+dp1[0][cur_r-mid])
out = ' '.join(list(map(str,ans)))
print(out)