# Contest 1984, Problem C2: Magnitude (Hard Version)
# URL: https://codeforces.com/contest/1984/problem/C2

import sys

# only max and min value can get max k
input = sys.stdin.buffer.readline
p = 998244353
for _ in range(int(input())):
    n = int(input())
    mx, mi = 0, 0
    mxc, mic = 1, 0
    for x in map(int, input().split()):
        mx2 = max(mx + x, abs(mi + x))
        mxc2 = (int(mx + x == mx2) + int(abs(mx + x) == mx2)) * mxc + (
            int(mi + x == mx2) + int(abs(mi + x) == mx2)
        ) * mic
        mi += x
        mic2 = (1 + int(mi >= 0)) * mic + int(mx + x == mi != mx2) * mxc
        mx = mx2
        mxc, mic = mxc2 % p, mic2 % p
    print(mxc)
