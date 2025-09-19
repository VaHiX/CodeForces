# Contest 2091, Problem D: Place of the Olympiad
# URL: https://codeforces.com/contest/2091/problem/D

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m, k = map(int, input().split())
    x = (k - 1) // n + 1
    y = m - x
    print((m + 1 - 1) // (y + 1))
