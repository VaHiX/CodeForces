# Contest 2074, Problem D: Counting Points
# URL: https://codeforces.com/contest/2074/problem/D

import sys
from math import isqrt

input = sys.stdin.readline

for _ in range(int(input())):
    input()

    height = {}
    for center, radius in zip(map(int, input().split()), map(int, input().split())):
        for d in range(-radius, radius + 1):
            x = d - center
            height[x] = max(height.get(x, 0), isqrt(radius * radius - d**2))

    print(sum(height.values()) * 2 + len(height))
