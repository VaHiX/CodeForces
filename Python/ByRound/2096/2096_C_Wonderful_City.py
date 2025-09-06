# Contest 2096, Problem C: Wonderful City
# URL: https://codeforces.com/contest/2096/problem/C


def solve():
    n = int(input())
    heights = [list(map(int, input().split())) for i in range(n)]
    arr = list(map(int, input().split()))
    brr = list(map(int, input().split()))
    ans = 0
    for _ in range(2):
        dp0 = 0
        dp1 = arr[0]
        for i in range(1, n):
            ndp0 = ndp1 = 10**18
            d = [heights[i][j] - heights[i - 1][j] for j in range(n)]
            if 0 not in d:
                ndp0 = min(ndp0, dp0)
                ndp1 = min(ndp1, dp1 + arr[i])
            if 1 not in d:
                ndp0 = min(ndp0, dp1)
            if -1 not in d:
                ndp1 = min(ndp1, dp0 + arr[i])
            dp0, dp1 = ndp0, ndp1
        ans += min(dp0, dp1)
        for i in range(n):
            for j in range(i + 1, n):
                heights[i][j], heights[j][i] = heights[j][i], heights[i][j]
        arr = brr
    if ans >= 10**18:
        return -1
    return ans


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())
