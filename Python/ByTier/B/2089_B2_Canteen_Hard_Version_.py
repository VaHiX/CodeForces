# Contest 2089, Problem B2: Canteen (Hard Version)
# URL: https://codeforces.com/contest/2089/problem/B2

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solve646():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    if sum(a) == k:
        return 0
    for i in range(n):
        d = min(a[i], b[i])
        a[i] -= d
        b[i] -= d
    ps = [0] * (n + 1)
    j = 0
    for i in range(n):
        ps[i] = ps[i - 1] + a[i] - b[i]
        if ps[i] < ps[j]:
            j = i
    j += 1
    a = a[j:] + a[:j]
    b = b[j:] + b[:j]
    l, r = 0, n
    while l + 1 < r:
        m = (l + r) // 2
        aa = a[:]
        s = []
        for i in range(n):
            s.append(i)
            x = b[i]
            while x and s and i - s[-1] < m:
                d = min(x, aa[s[-1]])
                x -= d
                aa[s[-1]] -= d
                if aa[s[-1]] == 0:
                    s.pop()
        if sum(aa) <= k:
            r = m
        else:
            l = m
    return r


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())

sys.stdout.write("\n".join(map(str, res_test)))  # output all test
