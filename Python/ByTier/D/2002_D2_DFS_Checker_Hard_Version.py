# Contest 2002, Problem D2: DFS Checker (Hard Version)
# URL: https://codeforces.com/contest/2002/problem/D2

import sys
import os
import io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def make_graph(n, m, a):
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = a[(i >> 1) + 2], (i >> 1) + 2
        s[u + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s

def dfs(u, v, z, dist, a):
    while z[u] != z[v]:
        if dist[z[u]] >= dist[z[v]]:
            u = a[z[u]]
        else:
            v = a[z[v]]
    return u if dist[u] <= dist[v] else v

def solve():
    t = int(input())
    inf = pow(10, 9) + 1
    results = []

    for _ in range(t):
        n, q = map(int, input().split())
        a = [0] * 2 + list(map(int, input().split()))
        p = [0] + list(map(int, input().split()))
        G, s0 = make_graph(n, n - 1, a)
        
        cnt = [1] * (n + 1)
        for i in range(n, 1, -1):
            cnt[a[i]] += cnt[i]

        dist = [inf] * (n + 1)
        dist[1] = 0
        for i in range(2, n + 1):
            dist[i] = dist[a[i]] + 1

        z = list(range(n + 1))
        for i in range(1, n + 1):
            j, ma, di = i, -1, dist[i]
            for v in range(s0[i], s0[i + 1]):
                k = G[v]
                if dist[k] >= di and ma < cnt[k]:
                    j, ma = k, cnt[k]
            z[j] = z[i]

        ng = 0
        for i in range(1, n):
            if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                ng += 1

        for _ in range(q):
            x, y = map(int, input().split())
            indices_to_check = {i for i in [x - 1, x, y - 1, y] if 0 < i < n}

            for i in indices_to_check:
                if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                    ng -= 1

            p[x], p[y] = p[y], p[x]

            for i in indices_to_check:
                if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                    ng += 1

            results.append("YES" if ng == 0 else "NO")

    sys.stdout.write("\n".join(results) + "\n")

if __name__ == "__main__":
    solve()
