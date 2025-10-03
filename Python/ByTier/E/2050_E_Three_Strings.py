# Contest 2050, Problem E: Three Strings
# URL: https://codeforces.com/contest/2050/problem/E

for _ in range(int(input())):
    a = "-" + input()
    b = "-" + input()
    c = "-" + input()

    dp = [[10**5] * len(a) for _ in range(len(b))]
    dp[0][0] = 0

    for i in range(len(dp)):
        for j in range(len(dp[0])):
            if i != 0:
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + (c[i + j] != b[i]))
            if j != 0:
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + (c[i + j] != a[j]))
    print(dp[len(b) - 1][len(a) - 1])
