# Contest 2042, Problem D: Recommendations
# URL: https://codeforces.com/contest/2042/problem/D

import sys, os, io

input = lambda: sys.stdin.readline().rstrip()

res_test = []
for _ in range(int(input())):
    n = int(input())
    l, r = [0] * n, [0] * n
    for i in range(n):
        l[i], r[i] = map(int, input().split())
    res = [0] * n
    mx_l, mx_r = max(l), max(r)
    idx = list(range(n))
    for t in range(2):
        idx = sorted(idx, key=lambda x: (l[x] << 30) + mx_r - r[x])
        s = []
        for i in idx:
            while s and r[s[-1]] < r[i]:
                s.pop()
            if s:
                res[i] += l[i] - l[s[-1]]
            s.append(i)
        for i in range(n):
            r[i], l[i] = mx_l - l[i], mx_r - r[i]

    for ix in range(1, n):
        if l[idx[ix]] == l[idx[ix - 1]] and r[idx[ix]] == r[idx[ix - 1]]:
            res[idx[ix]] = res[idx[ix - 1]] = 0

    res_test.extend(res)

sys.stdout.write("\n".join(map(str, res_test)))  # output all test
