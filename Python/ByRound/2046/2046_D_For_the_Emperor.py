# Problem: CF 2046 D - For the Emperor!
# https://codeforces.com/contest/2046/problem/D

"""
Algorithm: Minimum Cost Flow with Tarjan's SCC + Dinic + SPFA

This solution solves the problem of finding the minimum number of plans to distribute to messengers 
so that every city in a directed graph receives at least one plan. The approach uses:
1. Tarjan's algorithm to find strongly connected components (SCCs)
2. Minimum cost flow on the condensed graph to determine optimal messenger distribution
3. Dinic's algorithm for max flow and SPFA for finding minimum cost augmenting paths

Time Complexity: O(V^3 * E) where V is number of nodes and E is number of edges
Space Complexity: O(V + E) for storing graph and auxiliary arrays
"""

import sys
from collections import deque

INF = int(1e9)
N = 210
M = 810
E = 2 * (N * 5 + M * 2)
sys.setrecursionlimit(1 << 25)
n = m = 0
tot = 0
to = [0] * M
nxt = [0] * M
fst = [0] * N
a = [0] * N


def add(ui, vi):
    global tot
    tot += 1
    to[tot] = vi
    nxt[tot] = fst[ui]
    fst[ui] = tot


Tot = 1
To = [0] * E
Nxt = [0] * E
Fst = [0] * (N * 3)
Wei = [0] * E
Cst = [0] * E


def add_edge(ui, vi, wi, ci):
    global Tot
    Tot += 1
    To[Tot] = vi
    Nxt[Tot] = Fst[ui]
    Wei[Tot] = wi
    Cst[Tot] = ci
    Fst[ui] = Tot


def Add(ui, vi, wi, ci):
    add_edge(ui, vi, wi, ci)
    add_edge(vi, ui, 0, -ci)


dis = [INF] * (N * 3)
cur = [0] * (N * 3)
inq = [False] * (N * 3)
vis = [False] * (N * 3)


def SPFA():
    global dis, cur, inq
    dis = [INF] * len(dis)
    cur[:] = Fst[:]
    q = deque()
    dis[S] = 0
    q.append(S)
    inq[S] = True
    while q:
        u = q.popleft()
        inq[u] = False
        i = Fst[u]
        while i:
            v = To[i]
            w = Wei[i]
            c = Cst[i]
            if dis[v] > dis[u] + c and w:
                dis[v] = dis[u] + c
                if not inq[v]:
                    q.append(v)
                    inq[v] = True
            i = Nxt[i]
    return dis[T]


def dinic(x=None, rd=INF):
    if x is None:
        x = S
    if x == T:
        return rd
    res = rd
    vis[x] = True
    i = cur[x]
    while i and res:
        cur[x] = i
        v = To[i]
        w = Wei[i]
        c = Cst[i]
        if not vis[v] and w > 0 and dis[v] == dis[x] + c:
            tmp = dinic(v, min(res, w))
            Wei[i] -= tmp
            Wei[i ^ 1] += tmp
            res -= tmp
        i = Nxt[i]
    vis[x] = False
    return rd - res


stk = [0] * N
sln = 0
dfn = [0] * N
low = [0] * N
ord = [0] * N
num = 0
sum_vals = [0] * N


def tarjan(x):
    global sln, tot, num
    sln += 1
    stk[sln] = x
    vis[x] = True
    tot += 1
    dfn[x] = low[x] = tot
    i = fst[x]
    while i:
        y = to[i]
        if not dfn[y]:
            tarjan(y)
            low[x] = min(low[x], low[y])
        elif vis[y]:
            low[x] = min(low[x], dfn[y])
        i = nxt[i]
    if dfn[x] == low[x]:
        num += 1
        while True:
            z = stk[sln]
            sln -= 1
            vis[z] = False
            ord[z] = num
            sum_vals[num] += a[z]
            if z == x:
                break


def init():
    global tot, sln, num
    tot = 0
    sln = 0
    num = 0
    for i in range(len(vis)):
        vis[i] = False
    for i in range(len(fst)):
        fst[i] = 0
    for i in range(len(Fst)):
        Fst[i] = 0
    for i in range(len(sum_vals)):
        sum_vals[i] = 0
    for i in range(len(dfn)):
        dfn[i] = 0


def solve():
    global n, m, T, S, Tot
    init()
    n, m = map(int, input().split())
    a_input = list(map(int, input().split()))
    for i in range(1, n + 1):
        a[i] = a_input[i - 1]
    for _ in range(m):
        u, v = map(int, input().split())
        add(u, v)
    for i in range(1, n + 1):
        if not dfn[i]:
            tarjan(i)
    for i in range(len(vis)):
        vis[i] = False
    Tot = 1
    for i in range(1, n + 1):
        j = fst[i]
        while j:
            k = to[j]
            x = ord[i]
            y = ord[k]
            if x != y:
                Add(x, y, INF, 0)
                Add(x, y + 2 * num, 1, -1)
            j = nxt[j]
    n = num
    S = 3 * n + 1
    T = S + 1
    for i in range(1, n + 1):
        Add(S, i + n, 1, 0)
        Add(i + n, i, 1, 0)
        if sum_vals[i]:
            Add(S, i, sum_vals[i], 0)
            Add(i + 2 * n, i + n, 1, 0)
            Add(i + n, T, 1, 0)
        else:
            Add(i + 2 * n, i + n, 1, -n - 1)
            Add(i + n, T, 1, n + 1)
    flow = cost = 0
    mflw = 0
    mcst = n
    while SPFA() < INF:
        while True:
            flow = dinic()
            if not flow:
                break
            mflw += flow
            mcst += flow * dis[T]
    if mcst > n or mcst < 0:
        print("-1")
    else:
        print(mcst)


if __name__ == "__main__":
    TT = int(input())
    for _ in range(TT):
        solve()


# https://github.com/VaHiX/CodeForces/