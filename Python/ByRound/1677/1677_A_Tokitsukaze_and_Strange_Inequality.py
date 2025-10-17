# Contest 1677, Problem A: Tokitsukaze and Strange Inequality
# URL: https://codeforces.com/contest/1677/problem/A

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    dp = [0] * n
    ans = 0
    for i in range(n - 1, -1, -1):
        cnt = 0
        for j in range(i - 1, -1, -1):
            if arr[j] < arr[i]:
                ans += cnt
            cnt += dp[j]
            if arr[j] > arr[i]:
                dp[j] += 1
    print(ans)
