# Contest 2046, Problem A: Swap Columns and Find a Path
# URL: https://codeforces.com/contest/2046/problem/A

import sys

data = sys.stdin.read().splitlines()
t = int(data[0])
for tc in range(1, 3 * t + 1, 3):
    n = int(data[tc])
    a1 = list(map(int, data[tc + 1].split()))
    a2 = list(map(int, data[tc + 2].split()))
    a = list(zip(a1, a2))
    print(max(map(min, a)) + sum(map(max, a)))
