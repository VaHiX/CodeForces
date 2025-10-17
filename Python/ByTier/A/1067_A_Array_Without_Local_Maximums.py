# Contest 1067, Problem A: Array Without Local Maximums
# URL: https://codeforces.com/contest/1067/problem/A

import sys

input = sys.stdin.readline
n = int(input())
nums = [int(x) for x in input().split()]
mod = 998244353
dp0 = [0] * 201
dp1 = [0] * 201
if nums[0] == -1:
    dp0 = [1] * 201
    dp0[0] = 0
else:
    dp0[nums[0]] = 1
ans = 0
for i in range(1, n):
    a = b = nex = 0
    dp01 = [0] * 201
    dp11 = [0] * 201
    for j in range(1, 201):
        if nums[i] == -1 or nums[i] == j:
            dp01[j] = (a + b) % mod
            dp11[j] = (dp0[j] + ans - b + mod) % mod
            nex = (nex + dp11[j]) % mod
        a = (a + dp0[j]) % mod
        b = (b + dp1[j]) % mod
    dp0 = dp01
    dp1 = dp11
    ans = nex
print(ans)
