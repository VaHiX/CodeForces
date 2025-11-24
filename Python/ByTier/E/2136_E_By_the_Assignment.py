# Problem: CF 2136 E - By the Assignment
# https://codeforces.com/contest/2136/problem/E

"""
E. By the Assignment

Purpose:
This code solves a problem where we are given an undirected connected graph with vertex weights,
some of which are missing (-1). We must assign values from 0 to V-1 to these missing vertices such that
the graph becomes "balanced". A balanced graph ensures all simple paths between any two vertices have the same XOR value.

Algorithm:
1. Finds bridges in the graph using Tarjan's algorithm.
2. Identifies connected components (biconnected components or "blocks") of non-bridge edges.
3. For each component, checks if it's bipartite and whether all specified vertex weights are consistent.
4. Counts free variables for assignment (components with no constraints).
5. Calculates number of valid assignments using modular exponentiation.

Time Complexity: O(n + m) per test case
Space Complexity: O(n + m)
"""

import sys
from collections import deque

MOD = 998244353


def read_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


it = iter(read_ints())
t = next(it)
out = []
for _ in range(t):
    n = next(it)
    m = next(it)
    V = next(it)
    a = [next(it) for _ in range(n)]
    head = [-1] * n
    to = [0] * (2 * m)
    nx = [0] * (2 * m)
    eid = [0] * (2 * m)
    eu = [0] * m
    ev = [0] * m
    ptr = 0
    for i in range(m):
        u = next(it) - 1
        v = next(it) - 1
        eu[i] = u
        ev[i] = v
        to[ptr] = v
        eid[ptr] = i
        nx[ptr] = head[u]
        head[u] = ptr
        ptr += 1
        to[ptr] = u
        eid[ptr] = i
        nx[ptr] = head[v]
        head[v] = ptr
        ptr += 1
    tin = [0] * n
    low = [0] * n
    parent = [-1] * n
    parent_e = [-1] * n
    it_idx = [-1] * n
    is_bridge = [False] * m
    timer = 0
    for s in range(n):
        if tin[s]:
            continue
        stack = [s]
        parent[s] = -1
        parent_e[s] = -1
        it_idx[s] = head[s]
        timer += 1
        tin[s] = low[s] = timer
        while stack:
            u = stack[-1]
            idx = it_idx[u]
            if idx == -1:
                stack.pop()
                p = parent[u]
                pe = parent_e[u]
                if p != -1:
                    if low[u] > tin[p]:
                        is_bridge[pe] = True
                    if low[p] > low[u]:
                        low[p] = low[u]
                continue
            it_idx[u] = nx[idx]
            v = to[idx]
            e = eid[idx]
            if e == parent_e[u]:
                continue
            if tin[v] == 0:
                parent[v] = u
                parent_e[v] = e
                it_idx[v] = head[v]
                timer += 1
                tin[v] = low[v] = timer
                stack.append(v)
            else:
                if low[u] > tin[v]:
                    low[u] = tin[v]
    deg_nb = [0] * n
    for u in range(n):
        i2 = head[u]
        while i2 != -1:
            e = eid[i2]
            if not is_bridge[e]:
                deg_nb[u] += 1
            i2 = nx[i2]
    color = [-1] * n
    comp_id = [-1] * n
    comp_cnt = 0
    free_vars = 0
    ok = True
    for s in range(n):
        if deg_nb[s] == 0 or comp_id[s] != -1:
            continue
        q = deque([s])
        color[s] = 0
        comp_id[s] = comp_cnt
        bip = True
        seen_value = None
        equal_ok = True
        has_any = False
        while q and ok:
            u = q.popleft()
            if a[u] != -1:
                if not has_any:
                    seen_value = a[u]
                    has_any = True
                elif a[u] != seen_value:
                    equal_ok = False
                    break
            i2 = head[u]
            while i2 != -1:
                v = to[i2]
                e = eid[i2]
                if is_bridge[e]:
                    i2 = nx[i2]
                    continue
                if comp_id[v] == -1:
                    comp_id[v] = comp_cnt
                    if color[v] == -1:
                        color[v] = color[u] ^ 1
                        q.append(v)
                else:
                    if color[v] == color[u]:
                        bip = False
                if color[v] == -1 and comp_id[v] == comp_cnt:
                    color[v] = color[u] ^ 1
                    q.append(v)
                i2 = nx[i2]
        if not equal_ok:
            ok = False
            break
        if not bip:
            if has_any and seen_value != 0:
                ok = False
                break
        else:
            if not has_any:
                free_vars += 1
        comp_cnt += 1
    if not ok:
        out.append("0")
        continue
    for i in range(n):
        if deg_nb[i] == 0:
            if a[i] == -1:
                free_vars += 1
    ans = pow(V % MOD, free_vars, MOD) if ok else 0
    out.append(str(ans % MOD))
print("\n".join(out))


# https://github.com/VaHiX/codeForces/