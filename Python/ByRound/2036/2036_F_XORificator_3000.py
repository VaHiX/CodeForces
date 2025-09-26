# Contest 2036, Problem F: XORificator 3000
# URL: https://codeforces.com/contest/2036/problem/F

import sys

input = sys.stdin.readline


def fn(l, r, i, k):
    rg = lambda a, b: [a - 1, 1, a, 0][(a - 1) & 3] ^ [b, 1, b + 1, 0][b & 3]
    hi = rg((l - 1 - k + (1 << i)) >> i, (r - k) >> i) << i
    lo = k * (((r - k) >> i) - ((l - k - 1) >> i) & 1)
    print(rg(l, r) ^ hi ^ lo)


for _ in range(int(input())):
    l, r, i, k = list(map(int, input().split()))
    fn(l, r, i, k)
