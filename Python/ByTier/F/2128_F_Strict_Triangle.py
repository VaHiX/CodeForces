# Contest 2128, Problem F: Strict Triangle
# URL: https://codeforces.com/contest/2128/problem/F

import heapq

baku = []
INF = 10**18
for _ in range(int(input())):
    n, m, k = [int(t) for t in input().split()]
    k -= 1

    edges = [[] for _ in range(n)]
    for _ in range(m):
        a, b, l, r = [int(t) for t in input().split()]
        a -= 1
        b -= 1
        edges[a].append((b, l, r))
        edges[b].append((a, l, r))

    dr = [INF] * n
    h = [(0, k)]
    while h:
        d, u = heapq.heappop(h)
        if dr[u] < INF:
            continue
        dr[u] = d

        for v, _, r in edges[u]:
            if dr[v] < INF:
                continue
            heapq.heappush(h, (d + r, v))

    cap = [INF] * n
    h = [(-dr[0], 0)]
    while h:
        c, u = heapq.heappop(h)
        if cap[u] < INF:
            continue
        cap[u] = c

        for v, l, _ in edges[u]:
            if cap[v] < INF:
                continue
            nc = max(-dr[v], c + l)
            if nc < dr[v]:
                heapq.heappush(h, (nc, v))
    baku.append("YES" if cap[n - 1] < INF else "NO")
print(*baku)
