# Contest 2089, Problem B1: Canteen (Easy Version)
# URL: https://codeforces.com/contest/2089/problem/B1

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solve646():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ps = [0] * (n + 1)
    j = 0
    for i in range(n):
        ps[i] = ps[i - 1] + a[i] - b[i]
        if ps[i] < ps[j]:
            j = i
    j += 1
    a = a[j:] + a[:j]
    b = b[j:] + b[:j]
    i = res = 0
    while i < n:
        if a[i] > b[i]:
            s = []
            c, j = 0, i
            while j < n:
                c = b[j] - a[j]
                if c < 0:
                    s.append(c)
                else:
                    while s and c + s[-1] >= 0:
                        c += s.pop()
                    if not s:
                        break
                    s[-1] += c
                j += 1
            res = max(res, j - i)
            i = j
        else:
            i += 1
    return res + 1


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())

sys.stdout.write("\n".join(map(str, res_test)))  # output all test
