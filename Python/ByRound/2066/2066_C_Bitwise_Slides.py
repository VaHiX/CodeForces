# Contest 2066, Problem C: Bitwise Slides
# URL: https://codeforces.com/contest/2066/problem/C

from sys import stdin

input = lambda: stdin.readline().rstrip()
from collections import defaultdict
from random import randint

mod = 1000000007


def solve():
    n = int(input())
    rd = randint(1, (1 << 30) - 1)
    xor = [rd]
    for x in map(int, input().split()):
        xor.append(xor[-1] ^ x)

    dp = defaultdict(int)
    dp[rd] = 1
    for i in range(n):
        l, r = xor[i], xor[i + 1]
        dp[l] = (dp[l] * 3 + dp[r] * 2) % mod
    return sum(dp.values()) % mod


for _ in range(int(input())):
    print(solve())
