# Contest 1967, Problem A: Permutation Counting
# URL: https://codeforces.com/contest/1967/problem/A

import sys

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


for __ in range(fg()):
    n, k = fgh()
    a = fgh()
    l = 0
    r = 10**12 + 1
    while r - l > 1:
        m = (l + r) // 2
        z = 0
        for i in range(n):
            z += max(0, m - a[i])
        if z <= k:
            l = m
        else:
            r = m
    m = l
    z = 0
    t = 0
    for i in range(n):
        if a[i] > m:
            t += 1
        z += max(0, m - a[i])
    print((l - 1) * n + k - z + 1 + t)
