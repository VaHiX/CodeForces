# Contest 2009, Problem G1: Yunli's Subarray Queries (easy version)
# URL: https://codeforces.com/contest/2009/problem/G1

import sys; R = sys.stdin.readline
S = lambda: map(int,R().split())
P = print

for _ in range(int(R())):
    n,k,q = S()
    a = [*S()]
    for i in range(n): a[i] += n-1-i
    r = [0]*(n-k+1)
    M = 1<<(2*n).bit_length()
    t = [0]*2*M
    for i in range(n):
        y = a[i]+M
        t[y] += 1
        while y>1:
            y //= 2
            t[y] = max(t[2*y],t[2*y+1])
        if i>=k-1:
            r[i-k+1] = k-t[1]
            y = a[i-k+1]+M
            t[y] -= 1
            while y>1:
                y //= 2
                t[y] = max(t[2*y],t[2*y+1])
    for _ in range(q): P(r[[*S()][0]-1])