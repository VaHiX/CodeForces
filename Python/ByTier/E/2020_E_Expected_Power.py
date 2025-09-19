# Contest 2020, Problem E: Expected Power
# URL: https://codeforces.com/contest/2020/problem/E

import sys
input = sys.stdin.readline

def readList():
    return list(map(int, input().split()))
def readInt():
    return int(input())
def readInts():
    return map(int, input().split())
def readStr():
    return input().strip()


# BF-OB5, EC, DB, CC, CL
def solve():
    n, a, p = readInt(), readList(), readList()
    dp, ndp = [0] * 1024, [0] * 1024
    dp[0] = 1
    v = 10**4
    for ai, pi in zip(a, p):
        for j in range(1024):
            ndp[j] = ((dp[j] * (v - pi)) + dp[j ^ ai] * pi) % m
        dp, ndp = ndp, dp
    ans = 0
    for i in range(1024):
        ans += (i**2 * dp[i]) % m
        ans %= m
    dv = pow(v, m - 2, m)
    return ((ans % m) * pow(dv, n, m)) % m

m = 10**9 + 7
for _ in range(int(input())):
    print(solve())