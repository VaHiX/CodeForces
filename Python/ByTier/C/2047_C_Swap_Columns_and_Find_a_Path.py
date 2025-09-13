# Contest 2047, Problem C: Swap Columns and Find a Path
# URL: https://codeforces.com/contest/2047/problem/C

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    maxes = [max(i, j) for i, j in zip(a, b)]
    mins = [min(i, j) for i, j in zip(a, b)]
    print(sum(maxes) + max(mins))
