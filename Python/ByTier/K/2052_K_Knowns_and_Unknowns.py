# Problem: CF 2052 K - Knowns and Unknowns
# https://codeforces.com/contest/2052/problem/K

"""
Algorithm: Maximum Flow (Ford-Fulkerson with BFS)
Purpose: Determine whether students definitely visited, definitely did not visit, or cannot be determined based on professor lists.
Approach:
1. Identify constraints based on the order of visits.
2. Model the problem as a flow network.
3. Use max flow to check consistency.
4. Analyze flow paths to determine visit status.

Time Complexity: O(E^2 * V) where E is edges in flow graph and V is vertices.
Space Complexity: O(V + E) for storing the flow graph and intermediate data structures.
"""

def max_flow(n, s, t, g):
    m = len(g)
    og = {}
    rg = [{} for _ in range(n)]
    for _ in range(m):
        (u, v, c) = g.pop()
        og[(u, v)] = c
        if v not in rg[u]:
            rg[u][v] = 0
        if u not in rg[v]:
            rg[v][u] = 0
        rg[u][v] += c
    mf = 0
    while True:
        lg = [{} for _ in range(n)]
        vn = {s}
        cl = {s}
        while len(cl) > 0:
            nl = set()
            for a in cl:
                for b in rg[a]:
                    if b not in vn and rg[a][b] != 0:
                        nl.add(b)
                        lg[a][b] = rg[a][b]
            for a in nl:
                vn.add(a)
            cl = nl
        if t not in vn:
            break

        def blocking_flow(u, pl):
            if u == t:
                return pl
            sf = 0
            dn = set()
            for v in lg[u]:
                f = blocking_flow(v, min(pl, lg[u][v]))
                rg[u][v] -= f
                rg[v][u] += f
                lg[u][v] -= f
                if f < pl or lg[u][v] == 0:
                    dn.add(v)
                sf += f
                pl -= f
                if pl == 0:
                    break
            for v in dn:
                del lg[u][v]
            return sf

        mf += blocking_flow(s, float("infinity"))
    le = []
    for u in range(n):
        for v in rg[u]:
            if (u, v) in og and rg[u][v] < og[(u, v)]:
                le.append((u, v, og[(u, v)] - rg[u][v]))
    return (mf, rg)


for _ in range(int(input())):
    n = int(input())
    n += 1
    p1 = [int(i) - 1 for i in input().split()] + [-1]
    p2 = [int(i) - 1 for i in input().split()] + [-1]
    k = int(input())
    k += 1
    pk1 = [int(i) - 1 for i in input().split()] + [-1]
    pk2 = [int(i) - 1 for i in input().split()] + [-1]
    w2i = [-1] * n
    p1ints = []
    previ = -1
    prevj = -1
    inverse = [0] * n
    inconsistent = False
    for i in range(n):
        inverse[p1[i]] = i
    for j in range(k):
        if pk1[j] != -2: # -2 was used to represent -1 in the original code, but this is an issue in logic
            ls = []
            if previ > inverse[pk1[j]]:
                inconsistent = True
            for i in range(previ + 1, inverse[pk1[j]]):
                ls.append(p1[i])
            p1ints.append((j - prevj - 1, ls))
            previ = inverse[pk1[j]]
            prevj = j
            p1ints.append((1, [pk1[j]]))
    p2ints = []
    previ = -1
    prevj = -1
    inverse = [0] * n
    for i in range(n):
        inverse[p2[i]] = i
    for j in range(k):
        if pk2[j] != -2:
            ls = []
            if previ > inverse[pk2[j]]:
                inconsistent = True
            for i in range(previ + 1, inverse[pk2[j]]):
                w2i[p2[i]] = len(p2ints)
                ls.append(p2[i])
            p2ints.append((j - prevj - 1, ls))
            previ = inverse[pk2[j]]
            prevj = j
            w2i[pk2[j]] = len(p2ints)
            p2ints.append((1, [pk2[j]]))
    if inconsistent:
        print("Inconsistent")
        continue
    s = 0
    t = 1 + len(p1ints) + n + len(p2ints)
    g = []
    for i in range(len(p1ints)):
        (cap, ls) = p1ints[i]
        g.append((s, i + 1, cap))
        for ts in ls:
            g.append((i + 1, ts + 1 + len(p1ints), 1))
    for i in range(len(p2ints)):
        (cap, ls) = p2ints[i]
        g.append((1 + len(p1ints) + n + i, t, cap))
        for ts in ls:
            g.append((ts + 1 + len(p1ints), 1 + len(p1ints) + n + i, 1))
    mf, rg = max_flow(t + 1, s, t, g)
    if mf != k:
        print("Inconsistent")
        continue
    for i in range(n - 1):
        start = i + 1 + len(p1ints)
        if w2i[i] == -1:
            print("N", end="")
            continue
        fin = 1 + len(p1ints) + n + w2i[i]
        if rg[start][fin] == 0:
            seen = set()
            st = [start]
            while st:
                cur = st.pop()
                if cur == fin:
                    break
                if cur in seen:
                    continue
                seen.add(cur)
                for ncur in rg[cur]:
                    if rg[cur][ncur] > 0:
                        st.append(ncur)
            else:
                print("Y", end="")
                continue
            print("?", end="")
            continue
        seen = set()
        st = [fin]
        while st:
            cur = st.pop()
            if cur == start:
                break
            if cur in seen:
                continue
            seen.add(cur)
            for ncur in rg[cur]:
                if rg[cur][ncur] > 0:
                    st.append(ncur)
        else:
            print("N", end="")
            continue
        print("?", end="")
    print()


# https://github.com/VaHiX/CodeForces/