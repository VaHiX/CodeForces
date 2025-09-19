# Contest 8, Problem E: Beads
# URL: https://codeforces.com/contest/8/problem/E

n, k = map(int, input().split())


# n,k=3,1
################################################################################
def possible():
    dp = [[[0, 0], [0, 0]] for i in range(n)]
    if a[0] == 0 and a[n - 1] == -1:
        dp[0][1][0] = 1
        dp[0][0][1] = 1
    if a[0] == 0 and a[n - 1] == 0:
        dp[0][1][0] = 1
    if a[0] == 0 and a[n - 1] == 1:
        dp[0][0][1] = 1
    for i in range(1, n):
        j = n - 1 - i
        if i > j:
            i = i - 1
            break

        if i == j:
            if a[i] == -1:
                dp[i][0][0] = dp[i - 1][0][0] * 2
                dp[i][1][0] = dp[i - 1][1][0] * 2
                dp[i][0][1] = dp[i - 1][0][1]
            if a[i] == 0:
                dp[i][0][0] = dp[i - 1][0][0]
                dp[i][1][0] = dp[i - 1][1][0]
                dp[i][0][1] = dp[i - 1][0][1]
            if a[i] == 1:
                dp[i][0][0] = dp[i - 1][0][0]
                dp[i][1][0] = dp[i - 1][1][0]
            break

        if a[i] == -1:
            dp[i][0][0] = dp[i - 1][0][0] * 4 + dp[i - 1][1][0] + dp[i - 1][0][1]
            dp[i][1][0] = dp[i - 1][1][0] * 2
            dp[i][0][1] = dp[i - 1][0][1] * 2
        if a[i] == 0 and a[j] == -1:
            dp[i][0][0] = dp[i - 1][0][0] * 2 + dp[i - 1][1][0] + dp[i - 1][0][1]
            dp[i][1][0] = dp[i - 1][1][0]
            dp[i][0][1] = dp[i - 1][0][1]
        if a[i] == 0 and a[j] == 0:
            dp[i][0][0] = dp[i - 1][0][0] + dp[i - 1][0][1]
            dp[i][1][0] = dp[i - 1][1][0]
        if a[i] == 0 and a[j] == 1:
            dp[i][0][0] = dp[i - 1][0][0] + dp[i - 1][1][0]
            dp[i][0][1] = dp[i - 1][0][1]
        if a[i] == 1 and a[j] == -1:
            dp[i][0][0] = dp[i - 1][0][0] * 2
            dp[i][1][0] = dp[i - 1][1][0]
            dp[i][0][1] = dp[i - 1][0][1]
        if a[i] == 1 and a[j] == 0:
            dp[i][0][0] = dp[i - 1][0][0]
            dp[i][0][1] = dp[i - 1][0][1]
        if a[i] == 1 and a[j] == 1:
            dp[i][0][0] = dp[i - 1][0][0]
            dp[i][1][0] = dp[i - 1][1][0]

    sum = dp[i][0][0] + dp[i][0][1] + dp[i][1][0] + dp[i][1][1]
    judge = 1
    for i in range(n):
        if a[i] == 1:
            judge = 0
    if judge:
        sum = sum - 1

    return sum


################################################################################
a = [-1] * n
a[0] = 0
c = possible()
if k > c:
    print(-1)
else:
    for i in range(1, n):
        a[i] = 0
        c = possible()
        if k > c:
            k = k - c
            a[i] = 1
    out = ""
    for i in range(n):
        out += str(a[i])
    print(out)
