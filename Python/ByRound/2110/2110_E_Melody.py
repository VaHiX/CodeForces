# Contest 2110, Problem E: Melody
# URL: https://codeforces.com/contest/2110/problem/E

import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    visit = [0] * n
    mapv = {}  # compressor
    cv = 0
    mapp = {}  # compressor
    cp = 0
    edge = []
    for i in range(n):
        vi, pi = map(int, input().split())
        vi = mapv.setdefault(vi, cv)
        if vi == cv:
            cv += 1
        pi = mapp.setdefault(pi, cp)
        if pi == cp:
            cp += 1
        edge += [(vi, pi)]
    node = [[] for _ in range(cv + cp)]
    for i, e in enumerate(edge):
        vi, pi = e
        node[vi] += [i]
        node[pi + cv] += [i]
    edge = [(vi, pi + cv) for vi, pi in edge]
    cv = cv + cp
    # check euler
    vodd = []
    fail = False
    for i in range(cv):
        if len(node[i]) % 2 == 1:
            vodd += [i]
    if len(vodd) > 2:
        print("NO")
        continue
    cnode = vodd[1] if vodd else 0
    o = []
    visit = [0] * n
    edgeleft = [len(node[i]) for i in range(cv)]
    stack = [(-1, cnode)]
    while stack:
        prve, v = stack[-1]
        if edgeleft[v]:
            e = node[v].pop()
            if visit[e]:
                continue
            visit[e] = 1
            a, b = edge[e]
            edgeleft[a] -= 1
            edgeleft[b] -= 1
            next_node = a if a != v else b
            stack.append((e, next_node))
        else:
            stack.pop()
            if prve != -1:
                o += [prve + 1]
    if len(o) != n:
        print("NO")
    else:
        print("YES")
        print(*o)
