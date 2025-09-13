# Contest 2137, Problem E: Mexification
# URL: https://codeforces.com/contest/2137/problem/E

import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().split())
    a = [int(x) for x in input().split()]
    sm = [0] * 5
    op = [0] * 2
    for j in range(5):
        cnt = [0] * (n + 2)
        for x in a:
            cnt[x] += 1
        for i in range(n + 2):
            if not cnt[i]:
                m = i
                break
        ac = [0] * n
        for i in range(n):
            if a[i] < m and cnt[a[i]] == 1:
                ac[i] = a[i]
            else:
                ac[i] = m
        sm[j] = sum(ac)
        op[j % 2] = sum(ac)
        a = ac
    if k <= 5:
        print(sm[k - 1])
    else:
        print(op[(k & 1) ^ 1])


for _ in range(int(input())):
    solve()
