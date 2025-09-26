# Contest 2026, Problem E: Best Subsequence
# URL: https://codeforces.com/contest/2026/problem/E


from collections import defaultdict
from random import randint

import typing


class BipartiteMatching:

    def __init__(self, n: int, m: int) -> None:
        assert 0 < n
        assert 0 < m

        self._n = n
        self._m = m
        self._edge = [[] for _ in range(n)]

    def add_edge(self, a: int, b: int) -> bool:
        assert 0 <= a < self._n
        assert 0 <= b < self._m

        self._edge[a].append(b)

        return True

    def matching(self):
        n, m, edge = self._n, self._m, self._edge

        backpath = [-1] * n
        root = [-1] * n
        left2right = [-1] * n
        right2left = [-1] * m

        updated = True

        while updated:
            updated = False

            q = []
            q_front = 0

            for v in range(n):
                if left2right[v] == -1:
                    root[v] = v
                    q.append(v)

            while q_front < len(q):
                v = q[q_front]
                q_front += 1

                if left2right[root[v]] != -1:
                    continue

                for u in edge[v]:
                    if right2left[u] == -1:
                        while u != -1:
                            right2left[u] = v
                            left2right[v], u = u, left2right[v]
                            v = backpath[v]
                        updated = True
                        break

                    w = right2left[u]
                    if backpath[w] != -1:
                        continue
                    backpath[w] = v
                    root[w] = root[v]
                    q.append(w)

            if updated:
                backpath = [-1] * n
                root = [-1] * n

        return [(v, left2right[v]) for v in range(self._n) if left2right[v] != -1]


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    m = 60
    bm = BipartiteMatching(n, m)
    for i in range(n):
        for j in range(m):
            if a[i] >> j & 1:
                bm.add_edge(i, j)
    print(n - len(bm.matching()))
