# Contest 2042, Problem A: Greedy Monocarp
# URL: https://codeforces.com/contest/2042/problem/A

import sys

input = sys.stdin.readline

for _ in [0] * int(input()):
    n, k = map(int, input().split())
    l = sorted(map(int, input().split()))
    while l and k:
        if k < l[-1]:
            break
        k -= l.pop()
    print(k)
