# Contest 1290, Problem A: Mind Control
# URL: https://codeforces.com/contest/1290/problem/A

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, m, k = map(int, input().split())
    w = list(map(int, input().split()))
    if m < k + 2:
        w = w[:m] + w[-m:]
        print(max(w))
    else:
        c = 0
        d = [max(w[i], w[i + n - m]) for i in range(m)]
        for i in range(k + 1):
            c = max(c, min(d[i : i + m - k]), min(d[k - i : m - i]))
        print(c)
