# Problem: CF 1843 F2 - Omsk Metro (hard version)
# https://codeforces.com/contest/1843/problem/F2

"""
Algorithm: Tree Path Query with Segment Tree using Binary Lifting
Time Complexity: O(n log n) per test case
Space Complexity: O(n log n) per test case

This solution uses binary lifting to efficiently answer queries about 
whether there exists a subpath in a tree with a specific sum of weights.
The algorithm works by:
1. Building a tree with binary lifting for fast ancestor queries
2. Preprocessing prefix and suffix maximum/minimum sums for each node
3. For each query, finding the path between two nodes using binary lifting
4. Checking if the target sum k is achievable through the path
"""

import os
import sys

input = lambda: sys.stdin.readline().strip()

inf = float("inf")

def I():
    return input()

def II():
    return int(input())

def MII():
    return map(int, input().split())

def LI():
    return list(input().split())

def LII():
    return list(map(int, input().split()))

def LFI():
    return list(map(float, input().split()))

def GMI():
    return map(lambda x: int(x) - 1, input().split())

def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))

import os
import random
from io import BytesIO, IOBase


BUFSIZE = 4096

def main():
    q = II()

    parent = [[-1] * (q + 1) for _ in range(18)]
    values = [0] * (q + 1)
    depth = [0] * (q + 1)

    tot_sum = [[0] * (q + 1) for _ in range(18)]
    tot_sum[0][0] = values[0] = 1

    queries = []

    cur = 1
    for _ in range(q):
        query = LI()
        if query[0] == "+":
            v, x = int(query[1]) - 1, int(query[2])
            parent[0][cur] = v
            values[cur] = x
            depth[cur] = depth[v] + 1
            tot_sum[0][cur] = x

            for i in range(17):
                if parent[i][parent[i][cur]] == -1:
                    break
                parent[i + 1][cur] = parent[i][parent[i][cur]]
                tot_sum[i + 1][cur] = tot_sum[i][cur] + tot_sum[i][parent[i][cur]]
            cur += 1
        else:
            u, v, k = int(query[1]) - 1, int(query[2]) - 1, int(query[3])
            if depth[u] > depth[v]:
                u, v = v, u
            queries.append((u, v, k))

    res = [1] * len(queries)

    pre = [[0] * cur for _ in range(18)]
    suf = [[0] * cur for _ in range(18)]
    seg = [[0] * cur for _ in range(18)]

    for i in range(cur):
        if values[i] == 1:
            pre[0][i] = suf[0][i] = seg[0][i] = 1
        for j in range(17):
            p = parent[j][i]
            if p == -1:
                break
            pre[j + 1][i] = max(pre[j][i], pre[j][p] + tot_sum[j][i])
            suf[j + 1][i] = max(suf[j][p], suf[j][i] + tot_sum[j][p])
            seg[j + 1][i] = max(seg[j][i], seg[j][p], suf[j][i] + pre[j][p])

    for idx in range(len(queries)):
        u, v, k = queries[idx]
        su = au = 0
        sv = av = 0

        d = depth[v] - depth[u]
        while d:
            msk = d & -d
            j = msk.bit_length() - 1
            p = parent[j][v]
            sv, av = max(suf[j][v], sv + tot_sum[j][v]), max(
                av, seg[j][v], sv + pre[j][v]
            )
            v = p
            d -= msk

        if u == v:
            if k > max(av, sv + values[u]):
                res[idx] = 0

        else:
            for j in range(17, -1, -1):
                if parent[j][u] != parent[j][v]:
                    p = parent[j][v]
                    sv, av = max(suf[j][v], sv + tot_sum[j][v]), max(
                        av, seg[j][v], sv + pre[j][v]
                    )
                    v = p
                    p = parent[j][u]
                    su, au = max(suf[j][u], su + tot_sum[j][u]), max(
                        au, seg[j][u], su + pre[j][u]
                    )
                    u = p
            sv, av = max(suf[0][v], sv + tot_sum[0][v]), max(
                av, seg[0][v], sv + pre[0][v]
            )
            su, au = max(suf[0][u], su + tot_sum[0][u]), max(
                au, seg[0][u], su + pre[0][u]
            )
            u = parent[0][u]
            if k > max(au, av, su + sv + values[u]):
                res[idx] = 0

    pre = [[0] * cur for _ in range(18)]
    suf = [[0] * cur for _ in range(18)]
    seg = [[0] * cur for _ in range(18)]

    for i in range(cur):
        if values[i] == -1:
            pre[0][i] = suf[0][i] = seg[0][i] = -1
        for j in range(17):
            p = parent[j][i]
            if p == -1:
                break
            pre[j + 1][i] = min(pre[j][i], pre[j][p] + tot_sum[j][i])
            suf[j + 1][i] = min(suf[j][p], suf[j][i] + tot_sum[j][p])
            seg[j + 1][i] = min(seg[j][i], seg[j][p], suf[j][i] + pre[j][p])

    for idx in range(len(queries)):
        if res[idx] == 0:
            continue
        u, v, k = queries[idx]
        su = au = 0
        sv = av = 0

        d = depth[v] - depth[u]
        while d:
            msk = d & -d
            j = msk.bit_length() - 1
            p = parent[j][v]
            sv, av = min(suf[j][v], sv + tot_sum[j][v]), min(
                av, seg[j][v], sv + pre[j][v]
            )
            v = p
            d -= msk

        if u == v:
            if k < min(av, sv + values[u]):
                res[idx] = 0

        else:
            for j in range(17, -1, -1):
                if parent[j][u] != parent[j][v]:
                    p = parent[j][v]
                    sv, av = min(suf[j][v], sv + tot_sum[j][v]), min(
                        av, seg[j][v], sv + pre[j][v]
                    )
                    v = p
                    p = parent[j][u]
                    su, au = min(suf[j][u], su + tot_sum[j][u]), min(
                        au, seg[j][u], su + pre[j][u]
                    )
                    u = p
            sv, av = min(suf[0][v], sv + tot_sum[0][v]), min(
                av, seg[0][v], sv + pre[0][v]
            )
            su, au = min(suf[0][u], su + tot_sum[0][u]), min(
                au, seg[0][u], su + pre[0][u]
            )
            u = parent[0][u]
            if k < min(au, av, su + sv + values[u]):
                res[idx] = 0
    print("\n".join("YES" if x else "NO" for x in res))
    return


t = II()
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/