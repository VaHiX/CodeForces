# Contest 2110, Problem D: Fewer Batteries
# URL: https://codeforces.com/contest/2110/problem/D

import sys

input = sys.stdin.readline


def can_reach(n, adj, b, S):
    H = [-1] * (n + 1)
    H[1] = min(b[1], S)
    for u in range(1, n + 1):
        if H[u] < 0:
            continue
        hu = H[u]
        for v, w in adj[u]:
            if hu >= w:
                H[v] = max(H[v], min(hu + b[v], S))
    return H[n] >= 0


t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    b = [0] + list(map(int, input().split()))
    adj = [[] for _ in range(n + 1)]
    maxw = 0
    for _ in range(m):
        s, t_, w = map(int, input().split())
        adj[s].append((t_, w))
        maxw = max(maxw, w)

    lo, hi, ans = 0, maxw, -1
    while lo <= hi:
        mid = (lo + hi) // 2
        if can_reach(n, adj, b, mid):
            ans = mid
            hi = mid - 1
        else:
            lo = mid + 1

    print(ans)
