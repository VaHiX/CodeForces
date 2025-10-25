# Contest 2092, Problem E: She knows...
# URL: https://codeforces.com/contest/2092/problem/E

import os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

mod = 1000000007


def pw(a, b):
    ret = 1
    while b:
        if b & 1:
            ret = ret * a % mod
        a = a * a % mod
        b >>= 1
    return ret


T = int(input())
for _ in range(T):
    n, m, k = map(int, input().split())
    edge = 2 * n + 2 * m - 8
    cnt = 0
    for _ in range(k):
        i, j, c = map(int, input().split())
        if (i in [1, n]) ^ (j in [1, m]):
            edge -= 1
            cnt += c
    if edge:
        print(pw(2, n * m - k - 1))
    else:
        if cnt & 1:
            print(0)
        else:
            print(pw(2, n * m - k))
