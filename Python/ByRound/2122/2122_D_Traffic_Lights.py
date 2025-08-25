# Contest 2122, Problem D: Traffic Lights
# URL: https://codeforces.com/contest/2122/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve646():
    n, m = map(int, input().split())
    adj = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int, input().split())
        u, v = u - 1, v - 1
        adj[u].append(v)
        adj[v].append(u)
    n2 = 2 * n + 1
    d = [n2] * n
    fr = [1] * n
    fr[0] = d[0] = 0
    q = [0]
    t, mx_t = 0, n2
    while t + 1 < mx_t:
        nd = [n2] * n
        for u in q:
            deg = len(adj[u])
            v = adj[u][t % deg]
            if nd[v] > d[u]:
                nd[v] = d[u]
                if fr[v]:
                    q.append(v)
                    fr[v] = 0
                if v == n - 1:
                    mx_t = min(mx_t, t + 1)
            if nd[u] > d[u] + 1:
                nd[u] = d[u] + 1
                if fr[u]:
                    q.append(u)
                    fr[u] = 0
        t, d = t + 1, nd
    return [mx_t, d[-1]]


res_test = []
for _ in range(int(input())):
    res_test.append(" ".join(map(str, solve646())))
sys.stdout.write("\n".join(res_test))
