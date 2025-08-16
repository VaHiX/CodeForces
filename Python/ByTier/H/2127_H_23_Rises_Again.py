# Contest 2127, Problem H: 23 Rises Again
# URL: https://codeforces.com/contest/2127/problem/H

import sys
import random
from collections import defaultdict

input = sys.stdin.readline

P = 998244353
random.seed(P)


def solve():
    n, m = map(int, input().split())
    deg = [0] * (n + 1)
    G = defaultdict(list)
    E = []
    chs = [0] * m

    for _ in range(m):
        u, v = map(int, input().split())
        E.append((u, v))

    NUM = 10000
    TRY = n * n * NUM
    ans = 0

    for _ in range(TRY):
        id = random.randint(0, m - 1)
        if chs[id]:
            continue
        u, v = E[id]
        if deg[u] == 2 and deg[v] == 2:
            continue
        if deg[u] < 2 and deg[v] < 2:
            deg[u] += 1
            deg[v] += 1
            chs[id] = 1
            ans += 1
            G[u].append((v, id))
            G[v].append((u, id))
        else:
            if deg[v] == 2:
                u, v = v, u
            assert deg[v] < 2
            assert deg[u] == 2
            pos = random.randint(0, 1)
            if len(G[u]) < 2:
                continue
            G[u][pos], G[u][1] = G[u][1], G[u][pos]
            ov, oid = G[u][1]
            if G[ov][0][1] == oid:
                G[ov][0], G[ov][-1] = G[ov][-1], G[ov][0]
            G[ov].pop()
            deg[u] -= 1
            deg[ov] -= 1
            chs[oid] = 0
            G[u].pop()

            deg[u] += 1
            deg[v] += 1
            chs[id] = 1
            G[u].append((v, id))
            G[v].append((u, id))

    print(ans)


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == '__main__':
    main()