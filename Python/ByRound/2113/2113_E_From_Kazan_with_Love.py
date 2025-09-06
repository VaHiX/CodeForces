# Contest 2113, Problem E: From Kazan with Love
# URL: https://codeforces.com/contest/2113/problem/E

baku = []
for _ in range(int(input())):
    n, m, start, goal = [int(t) for t in input().split()]
    start -= 1
    goal -= 1

    edges = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = [int(t) - 1 for t in input().split()]
        edges[a].append(b)
        edges[b].append(a)

    par = [0] * n
    depth = [0] * n
    stack = [0]
    while stack:
        a = stack.pop()
        p = par[a]
        for b in edges[a]:
            if b == p:
                continue
            par[b] = a
            depth[b] = depth[a] + 1
            stack.append(b)

    def path(x, y):
        p = [x]
        q = [y]
        for _ in range(depth[x] - depth[y]):
            p.append(par[p[-1]])
        for _ in range(depth[y] - depth[x]):
            q.append(par[q[-1]])
        while p[-1] != q[-1]:
            p.append(par[p[-1]])
            q.append(par[q[-1]])
        return p + q[-2::-1]

    paths = [path(*[int(t) - 1 for t in input().split()]) for _ in range(m)]
    paths.sort(key=lambda x: -len(x))

    v = [0] * n
    v[start] = 1
    front = {start}
    clock = 1
    tot = 1
    while tot and not v[goal]:
        nfront = set()
        for f in front:
            for e in edges[f]:
                if v[e]:
                    continue
                v[e] = 1
                tot += 1
                nfront.add(e)
        for p in paths:
            if len(p) <= clock:
                break
            b = p[clock]
            if not v[b]:
                continue
            v[b] = 0
            tot -= 1
            nfront.discard(b)
            for e in edges[b]:
                if v[e]:
                    nfront.add(e)
        front = nfront
        clock += 1
    baku.append(clock if tot else -1)
print(*baku)
