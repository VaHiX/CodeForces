# Contest 2067, Problem E: White Magic
# URL: https://codeforces.com/contest/2067/problem/E

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = set()
    x = a.index(0) if 0 in a else -1
    mex = 0
    for j in range(n - 1, -1, -1):
        if a[j] < mex:
            mex = 0
            break
        if a[j] or j == x:
            s.add(a[j])
            while mex in s:
                mex += 1
    print(n - a.count(0) + int(mex != 0))
