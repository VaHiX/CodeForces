# Problem: CF 1912 C - Cactus Transformation
# https://codeforces.com/contest/1912/problem/C

"""
Cactus Transformation Problem

Algorithm:
- The solution is based on transforming one cactus graph into another by removing and adding edges
- Key techniques used:
  1. Finding cycles in the cactus graph using DFS
  2. Decomposing cactus into triangles and free edges
  3. Using matching algorithms to rearrange edges
  4. BFS to find distances for optimization

Time Complexity: O(n * m) where n is number of vertices and m is number of edges
Space Complexity: O(n + m) for storing graph and auxiliary data structures

Approach:
1. Parse input to get two cactus graphs
2. Identify cycles and decompose the first cactus into triangles and free edges
3. Perform operations to convert first cactus to second one using BFS distances
4. Apply matching algorithm to ensure correct edge arrangement
5. Output sequence of operations

The algorithm handles the specific constraints of cactus graphs where each edge belongs to at most one cycle.
"""

n, m = [int(t) for t in input().split()]


def read_graph():
    edges = [set() for _ in range(n)]
    for _ in range(m):
        a, b = [int(t) - 1 for t in input().split()]
        edges[a].add(b)
        edges[b].add(a)
    return edges


def solve():
    edges = read_graph()

    moves = []

    def move(a, b, c, d):
        # Remove edge (a,b) and add edge (c,d)
        edges[a].remove(b)
        edges[b].remove(a)
        edges[c].add(d)
        edges[d].add(c)
        moves.append((a, b, c, d))

    cycs = []
    par = [-1] * n
    vis = [0] * n
    stack = [0]
    mark = [0] * n
    while stack:
        a = stack.pop()
        if vis[a]:
            continue
        vis[a] = 1

        for b in edges[a]:
            if b == par[a]:
                continue
            if vis[b]:
                c = a
                cyc = [c]
                while c != b:
                    mark[c] = 1
                    c = par[c]
                    cyc.append(c)
                cycs.append(cyc)
            else:
                stack.append(b)
                par[b] = a

    tri = []
    free = []
    for i in range(1, n):
        if not mark[i]:
            free.append((i, par[i]))
    for cyc in cycs:
        if len(cyc) == 3:
            tri.append(cyc)
            continue

        move(cyc[0], cyc[-1], cyc[-1], cyc[-3])
        for i in range(len(cyc) - 3):
            free.append((cyc[i], cyc[i + 1]))
        tri.append((cyc[-3], cyc[-2], cyc[-1]))

    st, ot = free[0]
    if st == n - 1:
        st, ot = ot, st

    upd = []
    for t in tri:
        if st in t:
            T = list(t)
            T.remove(st)
            x, y = T
            move(x, st, x, ot)
            move(y, st, y, ot)
            upd.append((ot, x, y))
        else:
            upd.append(t)
    tri = upd

    upd = []
    for e in free[1:]:
        if st in e:
            u = e[0] if e[1] == st else e[1]
            move(u, st, u, ot)
            upd.append((u, ot))
        else:
            upd.append(e)
    free = upd

    dist = [0] * n
    vis = [0] * n
    vis[n - 1] = 1
    queue = [n - 1]
    for a in queue:
        for b in edges[a]:
            if vis[b]:
                continue
            vis[b] = 1
            queue.append(b)
            dist[b] = dist[a] + 1

    pairs = []
    if ot != n - 1:
        move(st, ot, st, n - 1)
    for t in tri:
        x, y, z = sorted(t, key=lambda v: dist[v])
        pairs.append((y, z))
        if n - 1 in t:
            continue
        move(st, n - 1, st, x)
        move(y, x, y, st)
        move(z, x, z, st)
        move(st, x, st, n - 1)
        move(z, st, z, n - 1)
        move(y, st, y, n - 1)
    for e in free:
        if n - 1 in e:
            continue
        x, y = sorted(e, key=lambda v: dist[v])
        move(y, x, y, n - 1)

    k = len(pairs)
    match = [-1] * n
    for x, y in pairs:
        match[x] = y
        match[y] = x
    for i in range(0, 2 * k, 2):
        if match[i] == i + 1:
            continue

        st = 0
        while match[st] > -1:
            st += 1

        if match[i] > -1 and match[i + 1] > -1:
            x = match[i]
            y = match[i + 1]
            move(x, i, x, st)
            match[x] = st
            match[st] = x
            move(i + 1, y, i + 1, i)
            match[y] = -1
        elif match[i + 1] > -1:
            y = match[i + 1]
            move(i + 1, y, i + 1, i)
            match[y] = -1
        elif match[i] > -1:
            x = match[i]
            move(i, x, i, i + 1)
            match[x] = -1
        else:
            x = i
            while match[x] == -1:
                x += 1
            y = match[x]
            move(x, y, i, i + 1)
            match[x] = match[y] = -1
        match[i + 1] = i
        match[i] = i + 1
    return moves


if 2 * m == 3 * (n - 1):
    if read_graph() == read_graph():
        print("YES\n0")
    else:
        print("NO")
else:
    print("YES")
    m1 = solve()
    m2 = solve()
    print(len(m1) + len(m2))
    for m in m1:
        print(*[e + 1 for e in m])
    for m in reversed(m2):
        print(*[e + 1 for e in reversed(m)])


# https://github.com/VaHiX/CodeForces/