# Contest 2094, Problem D: Tung Tung Sahur
# URL: https://codeforces.com/contest/2094/problem/D

import sys

input = sys.stdin.readline

from itertools import groupby

ii = lambda: int(input())


def solve():
    p, s = input(), input()

    arr_p = [len([*b]) for a, b in groupby(p)]
    arr_s = [len([*b]) for a, b in groupby(s)]

    if p[0] != s[0] or len(arr_p) != len(arr_s):
        print("NO")
        return 0

    if all(a <= b <= a * 2 for a, b in zip(arr_p, arr_s)):
        print("YES")
    else:
        print("NO")


for _ in range(ii()):
    solve()
