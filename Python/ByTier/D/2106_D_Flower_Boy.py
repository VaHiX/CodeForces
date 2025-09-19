# Contest 2106, Problem D: Flower Boy
# URL: https://codeforces.com/contest/2106/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())

inf = 1 << 30


def solve():
    n, m = mii()
    A = lii()
    B = lii()
    pre = [-1] * (m + 1)
    j = 0
    for i in range(m):
        while j < n and A[j] < B[i]:
            j += 1
        pre[i + 1] = j
        if j < n:
            j += 1
    if pre[-1] < n:
        return 0
    suf = [n] * (m + 1)
    j = n - 1
    for i in range(m - 1, -1, -1):
        while j >= 0 and A[j] < B[i]:
            j -= 1
        suf[i] = j
        if j >= 0:
            j -= 1
    ans = inf
    for i in range(m):
        if pre[i] < suf[i + 1]:
            ans = min(ans, B[i])
    return ans if ans < inf else -1


for _ in range(ii()):
    print(solve())
