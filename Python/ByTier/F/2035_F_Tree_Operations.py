# Contest 2035, Problem F: Tree Operations
# URL: https://codeforces.com/contest/2035/problem/F

import sys


def dfs(u, f):
    now = 0
    for v in adj[u]:
        if v == f:
            continue
        now += dfs(v, u)
    if now + a[u] < D:
        return 0
    return now + a[u] - D


def check(x):
    global D
    D = x
    return dfs(root, 0) == 0


def dfs2(u, f):
    now = 0
    for v in adj[u]:
        if v == f:
            continue
        now += dfs2(v, u)
    now += a[u]
    d = D // n
    if u <= D % n:
        d += 1
    if now >= d:
        return now - d
    if (d - now) % 2 == 0:
        return 0
    return 1


def solve():
    global adj, a, root, D, n
    n, root = map(int, input().split())
    a = list(map(int, input().split()))
    adj = [[] for _ in range(n + 10)]
    a = [0] + a
    for _ in range(n - 1):
        u, v = map(int, input().split())
        adj[u].append(v)
        adj[v].append(u)

    lo, hi = 0, int(1e9)
    min = int(1e9)

    while lo <= hi:
        m = (lo + hi) // 2
        if check(m):
            min = m
            hi = m - 1
        else:
            lo = m + 1
    ans = -1
    t = max(0, (min - 1) * n)
    for i in range(8 * n + 10):
        D = t
        now = dfs2(root, 0)
        if now == 0:
            ans = t
            break
        t += now
    print(ans)


if __name__ == "__main__":
    t = int(input())
    sys.setrecursionlimit(10**4)
    for _ in range(t):
        solve()
