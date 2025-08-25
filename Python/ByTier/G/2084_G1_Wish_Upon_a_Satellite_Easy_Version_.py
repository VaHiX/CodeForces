# Contest 2084, Problem G1: Wish Upon a Satellite (Easy Version)
# URL: https://codeforces.com/contest/2084/problem/G1

import sys

INF = int(1e18)


def chmax(a, b):
    return max(a, b)


def solve():
    n = int(input())
    f = [-1] * n

    x_values = list(map(int, input().split()))
    for i in range(n):
        x = x_values[i] - 1
        if x >= 0:
            f[x] = i % 2

    n0 = (n + 1) // 2
    n1 = n // 2
    dp = [-INF] * (n1 + 1)
    dp[0] = 0

    for x in range(n):
        for b in range(min(x, n1), -1, -1):
            a = x - b
            if b < n1 and f[x] != 0:
                dp[b + 1] = chmax(dp[b + 1], dp[b] + (x + 1) * (n0 - a + b + 1))
            if f[x] != 1:
                dp[b] += (x + 1) * (n1 - b + a + 1)
            else:
                dp[b] = -INF

    print(dp[n1])


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()
