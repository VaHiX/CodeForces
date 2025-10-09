# Contest 1819, Problem A: Constructive Problem
# URL: https://codeforces.com/contest/1819/problem/A

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    s = set(a)
    mex = 0
    while mex in s:
        mex += 1
    if mex + 1 not in s:
        if mex != n:
            print("Yes")
        else:
            print("No")
        return
    left = n
    right = -1
    for i in range(n):
        if a[i] == mex + 1:
            left = min(left, i)
            right = i
    b = a.copy()
    for i in range(n):
        if left <= i <= right:
            b[i] = mex
    t = set(b)
    mex2 = 0
    while mex2 in t:
        mex2 += 1
    if mex + 1 == mex2:
        print("Yes")
    else:
        print("No")


for _ in range(int(input())):
    solve()
