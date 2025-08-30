# Contest 2117, Problem F: Wildflower
# URL: https://codeforces.com/contest/2117/problem/F

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    G = [[] for i in range(N)]
    for i in range(N - 1):
        a, b = map(int, input().split())
        G[a - 1].append(b - 1)
        G[b - 1].append(a - 1)
    leaf = []
    for i in range(1, N):
        if len(G[i]) == 1:
            leaf.append(i)
    if len(leaf) > 2:
        print(0)
        continue
    mod = 10**9 + 7
    if len(leaf) == 1:
        result = pow(2, N, mod)
        print(result)
        continue
    a, b = leaf[:]
    n, m = 0, 0
    used = [False] * N
    used[a] = True
    used[b] = True
    while True:
        for c in G[a]:
            if used[c] == False:
                used[c] = True
                a = c
        n += 1
        if len(G[a]) > 2:
            break
        if a == 0:
            break
    used = [False] * N
    used[b] = True
    while True:
        for c in G[b]:
            if used[c] == False:
                used[c] = True
                b = c
        m += 1
        if len(G[b]) > 2:
            break
        if b == 0:
            break
    if n == m:
        result = pow(2, N - 2 * m + 1, mod)
    else:
        result = pow(2, N - 2 * min(n, m) - 1, mod) + pow(2, N - 2 * min(n, m), mod)
        result %= mod
    print(result)
