# Contest 933, Problem A: A Twisty Movement
# URL: https://codeforces.com/contest/933/problem/A


def solve() -> None:
    n = int(input())
    arr = list(map(int, input().split()))

    dp = [0] * 5

    for x in arr:
        if x == 1:
            dp[1] += 1
            dp[2] = max(dp[1], dp[2])
            dp[3] = max(dp[2], dp[3] + 1)
            dp[4] = max(dp[3], dp[4])
        else:
            dp[2] = max(dp[1], dp[2] + 1)
            dp[3] = max(dp[2], dp[3])
            dp[4] = max(dp[3], dp[4] + 1)

    print(dp[4])


# t = int(input())
# for _ in range(t):
solve()
