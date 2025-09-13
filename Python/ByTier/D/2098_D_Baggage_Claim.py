# Contest 2098, Problem D: Baggage Claim
# URL: https://codeforces.com/contest/2098/problem/D

"""
url: https://codeforces.com/contest/2098/problem/D
"""

import sys

input = sys.stdin.readline

MOD = int(1e9 + 7)

for _ in range(int(input())):
    n, m, k = map(int, input().split())

    size = n * m
    pa = list(range(size))
    sz = [1] * size
    need = [0] * size
    cnt = [0] * size
    fixed = [False] * size

    def find(x):
        while pa[x] != x:
            pa[x] = pa[pa[x]]
            x = pa[x]
        return x

    def merge(u, v):
        u, v = find(u), find(v)
        if u != v:
            pa[v] = u
            sz[u] += sz[v]
            need[u] += need[v]
        need[u] += 1

    def id(x, y):
        return (x - 1) * m + (y - 1)

    p = []
    ok = True
    for _ in range(k + 1):
        x, y = map(int, input().split())
        p.append((x, y))
        cid = id(x, y)
        cnt[cid] += 1
        if cnt[cid] > 1:
            ok = False

    if not ok:
        print(0)
        continue

    for i in range(k):
        x1, y1 = p[i]
        x2, y2 = p[i + 1]
        if abs(x1 - x2) + abs(y1 - y2) != 2:
            print(0)
            break
    else:
        for i in range(k):
            x1, y1 = p[i]
            x2, y2 = p[i + 1]
            if abs(x1 - x2) == 2 or abs(y1 - y2) == 2:
                u = id((x1 + x2) // 2, (y1 + y2) // 2)
                u = find(u)
                need[u] += 1
                fixed[u] = True
            else:
                u = id(x1, y2)
                v = id(x2, y1)
                merge(u, v)

        ans = 1
        vis = [False] * size

        for i in range(size):
            if fixed[i]:
                p_root = find(i)
                fixed[p_root] = True

        for i in range(size):
            p_root = find(i)
            if vis[p_root]:
                continue
            vis[p_root] = True

            if need[p_root] > sz[p_root] or need[p_root] < sz[p_root] - 1:
                ans = 0
                break
            if need[p_root] == sz[p_root] - 1:
                ans = ans * sz[p_root] % MOD
            elif not fixed[p_root]:
                ans = ans * 2 % MOD

        print(ans)
