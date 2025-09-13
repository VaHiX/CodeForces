# Contest 256, Problem A: Almost Arithmetical Progression
# URL: https://codeforces.com/contest/256/problem/A

for _ in range(1):  # int(input())):
    n = int(input())
    a = [0] + [*map(int, input().split())]
    dp = [[0 for i in range(n + 1)] for j in range(n + 1)]
    for i in range(1, n + 1):
        cur = 0
        for j in range(i):
            dp[i][j] = dp[j][cur] + 1
            cur = j if (a[i] == a[j]) else cur
    print(max([max(i) for i in dp]))
