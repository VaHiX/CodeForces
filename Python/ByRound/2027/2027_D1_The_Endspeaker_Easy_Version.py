# Contest 2027, Problem D1: The Endspeaker (Easy Version)
# URL: https://codeforces.com/contest/2027/problem/D1

import sys

inp = lambda func=int: list(map(func, sys.stdin.readline().split()))
t = inp()[0]
for _ in range(t):
    n, m = inp()
    a = inp()
    b = inp()

    pre = [0] * (n + 1)
    for i in range(n):
        pre[i + 1] = pre[i] + a[i]

    dp = [float("inf")] * (n + 1)
    dp[0] = 0

    for k in range(1, m + 1):
        j = 0
        for i in range(1, n + 1):
            while j < i and pre[i] - pre[j] > b[k - 1]:
                j += 1
            if j < i:
                dp[i] = min(dp[i], dp[j] + m - k)

    print(dp[n] if dp[n] != float("inf") else -1)
