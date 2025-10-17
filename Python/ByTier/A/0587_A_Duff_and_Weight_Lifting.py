# Contest 587, Problem A: Duff and Weight Lifting
# URL: https://codeforces.com/contest/587/problem/A

from sys import stdin

input, Max = lambda: stdin.buffer.readline().decode(), 10**6 + 100
n, mem, ans = int(input()), [0] * Max, 0
for i in [int(x) for x in input().split()]:
    mem[i] += 1
for i in range(Max - 1):
    mem[i + 1] += mem[i] >> 1
    ans += mem[i] & 1
print(ans)
