# Contest 2124, Problem F1: Appending Permutations (Easy Version)
# URL: https://codeforces.com/contest/2124/problem/F1

from sys import stdin

input = lambda: stdin.readline().rstrip()
MOD = 998244353


def min2(x, y):
    return x if x < y else y


def solve():
    n, m = map(int, input().split())
    b = [[n] * (n + 1) for _ in range(n + 1)]
    for _ in range(m):
        i, x = (num - 1 for num in map(int, input().split()))
        b[i][x] = i
    for p in range(n - 1, -1, -1):
        for i in range(n):
            b[p][i] = min2(b[p][i], b[p + 1][i + 1])

    hav = [[0] * (n + 1) for _ in range(n + 2)]
    dp = [1] + [0] * n

    for l in range(n + 1):
        l1 = l + 1
        for i in range(1, n - l + 1):
            x = dp[l]
            if l - i >= 0 and b[l - i][0] >= l:
                x -= dp[l - i]
            r1 = b[l][i] + 1
            hav[l1][i] = (hav[l1][i] + x) % MOD
            hav[r1][i] = (hav[r1][i] - x) % MOD

        for i in range(n + 1):
            hav[l1][i] = (hav[l1][i] + hav[l][i]) % MOD
        for i in range(1, b[l][0] - l + 1):
            dp[l + i] = (dp[l + i] + dp[l] + hav[l][i]) % MOD
    return dp[-1]


for _ in range(int(input())):
    print(solve())
