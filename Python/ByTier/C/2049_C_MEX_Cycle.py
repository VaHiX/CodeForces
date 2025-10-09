# Contest 2049, Problem C: MEX Cycle
# URL: https://codeforces.com/contest/2049/problem/C

import math
import sys

input = sys.stdin.readline


def main():
    n, x, y = map(int, input().split())
    ans = [0] * n
    x -= 1
    y -= 1
    for i in range(n):
        ans[(x + i) % n] = i % 2
    if n % 2 == 1 or (x - y) % 2 == 0:
        ans[x] = 2
    print(" ".join(map(str, ans)))


for _ in range(int(input())):
    main()
