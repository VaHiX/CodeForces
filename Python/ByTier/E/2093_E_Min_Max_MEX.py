# Contest 2093, Problem E: Min Max MEX
# URL: https://codeforces.com/contest/2093/problem/E

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N, K = map(int, input().split())
    A = list(map(int, input().split()))
    l = 0
    r = N
    while True:
        if l == r:
            break
        m = (l + r + 1) // 2
        v = [0] * m
        x = m
        count = 0
        for i in range(N):
            y = A[i]
            if y >= m:
                continue
            if v[y] == count:
                v[y] = count + 1
                x -= 1
                if x == 0:
                    count += 1
                    x = m
        if count >= K:
            l = m
        else:
            r = m - 1
    print(l)
