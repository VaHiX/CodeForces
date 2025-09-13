# Contest 2078, Problem B: Vicious Labyrinth
# URL: https://codeforces.com/contest/2078/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    if k % 2:
        print(*[n] * (n - 1) + [n - 1])
    else:
        print(*[n - 1] * (n - 2) + [n, n - 1])
