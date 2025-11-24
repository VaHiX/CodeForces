# Problem: CF 2120 G - Eulerian Line Graph
# https://codeforces.com/contest/2120/problem/G

"""
G. Eulerian Line Graph
Purpose:
    Determine if the k-th line graph L^k(G) of a given simple connected graph G has an Euler trail.

Algorithm/Techniques:
    - Graph theory and line graph properties
    - Eulerian trail characterization: A graph is Eulerian if and only if all vertices have even degree.
    - For line graphs L(G), the degree of each vertex in L(G) equals the degree of its corresponding edge in G.
    - The key idea is that L^k(G) has an Euler trail if and only if L^(k-1)(G) does, for k > 1,
      except when certain structural constraints are violated.

Time Complexity:
    O(n + m) per test case where n is number of vertices and m is the number of edges.
Space Complexity:
    O(n + m), used for storing adjacency list and auxiliary arrays.
"""

import sys
from collections import deque

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


for __ in range(fg()):
    n, m, k = fgh()
    a = [[] for i in range(n)]
    for i in range(m):
        u, v = fgh()
        u -= 1
        v -= 1
        a[u].append(v)
        a[v].append(u)
    cnt = 0
    for i in range(n):
        if len(a[i]) % 2:
            cnt += 1
    if cnt == 0:
        sd()
    else:
        cnt1 = 0
        cnt2 = 0
        powpow = 0
        d = [[0] * 2 for i in range(n)]
        # Count even and odd degree neighbors for each node
        for i in range(n):
            for j in a[i]:
                d[i][len(a[j]) % 2] += 1
                if (len(a[i]) + len(a[j])) % 2 == 0:
                    cnt2 += 1
                else:
                    cnt1 += 1
        # Special case when k = 1: L(G)
        if k == 1:
            if cnt1 <= 4:
                sd()
            else:
                df()
            continue
        # When all edges in L(G) have even degrees, it's always possible
        if cnt2 == 0:
            sd()
        else:
            # If no node has even degree edges, impossible
            if cnt1 == 0:
                sd()
                continue
            zz = 0
            for i in range(n):
                zz += d[i][0] * d[i][1]
            # Special case when k = 2: L^2(G)
            if k == 2:
                if zz <= 2:
                    sd()
                else:
                    df()
                continue
            # If no cross edges exist, impossible
            if zz == 0:
                sd()
                continue
            zzz = 0
            for i in range(n):
                zzz += 2 * d[i][0] * d[i][1] * (len(a[i]) - 2)
            # Further checking based on cross connections
            for i in range(n):
                for j in a[i]:
                    W = (len(a[i]) % 2) ^ (len(a[j]) % 2)
                    uy = 1 ^ W
                    for p in range(2):
                        xx = d[i][p]
                        yy = d[j][p ^ uy]
                        if len(a[j]) % 2 == p:
                            xx -= 1
                        if len(a[i]) % 2 == (p ^ uy):
                            yy -= 1
                        zzz += xx * yy
            # Divide by two since every pair counted twice
            zzz //= 2
            # Special case when k = 3: L^3(G)
            if k == 3:
                if zzz <= 2:
                    sd()
                else:
                    df()
                continue
            # If no cross edges in L^3, impossible
            if zzz == 0:
                sd()
                continue
            # Early termination conditions for higher powers
            if zz >= 4:
                df()
                continue
            if zzz >= 4:
                df()
                continue
            # BFS from leaves to calculate distances to nearest vertex with degree > 2
            q = deque()
            dist = [n] * n
            for i in range(n):
                if len(a[i]) == 1:
                    q.append(i)
                    dist[i] = 0
            while q:
                c = q.popleft()
                for u in a[c]:
                    if dist[u] > dist[c] + 1:
                        dist[u] = dist[c] + 1
                        q.append(u)
            # Find minimum distance from leaf to high-degree node
            mn = n
            for i in range(n):
                if len(a[i]) > 2:
                    mn = min(mn, dist[i])
            # If such path is long enough, we can construct Eulerian cycle
            if mn >= k:
                sd()
            else:
                df()


# https://github.com/VaHiX/codeForces/