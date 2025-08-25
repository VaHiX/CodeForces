# Contest 2045, Problem F: Grid Game 3-angle
# URL: https://codeforces.com/contest/2045/problem/F

import sys

input = sys.stdin.readline
from collections import defaultdict

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())

    # low = n + 10
    # curr = []

    seen = defaultdict(int)

    for _ in range(m):
        ri, ci, xi = map(int, input().split())

        """
        if ri < low:
            low = ri
            curr = []

        if ri == low:
            curr.append(xi)
        """

        ri %= k + 1
        xi %= k + 1

        seen[ri] ^= xi

    o = 0
    for v in seen:
        o += seen[v]

    if o:
        print("Anda")
    else:
        print("Kamu")
