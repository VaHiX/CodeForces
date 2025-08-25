# Contest 2096, Problem B: Wonderful Gloves
# URL: https://codeforces.com/contest/2096/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    l = list(map(int, input().split()))
    r = list(map(int, input().split()))
    a = sorted([min(l[j], r[j]) for j in range(n)])
    print(sum(l) + sum(r) - sum(a[: n - k]) - a[n - k] + 1)
