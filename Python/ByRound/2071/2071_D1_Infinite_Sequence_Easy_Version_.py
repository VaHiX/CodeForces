# Contest 2071, Problem D1: Infinite Sequence (Easy Version)
# URL: https://codeforces.com/contest/2071/problem/D1

import sys

input = sys.stdin.readline


def clc(m, n, pre):
    if m <= n:
        return pre[m]
    if m % 2 == 0:
        return clc(m // 2, n, pre) ^ pre[n]
    else:
        return pre[n]


def solve():
    n, l, r = map(int, input().split())
    ls = list(map(int, input().split()))
    if l <= n:
        print(ls[l - 1])
        return
    pre = [0] * (n + 1)
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] ^ ls[i - 1]
    if n % 2 == 0:
        ls.append(pre[(n + 1) // 2])
        pre.append(pre[n] ^ ls[-1])
        n += 1
    print(clc(l // 2, n, pre))


for _ in range(int(input())):
    solve()
