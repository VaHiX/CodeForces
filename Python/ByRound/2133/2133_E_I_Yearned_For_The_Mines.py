# Contest 2133, Problem E: I Yearned For The Mines
# URL: https://codeforces.com/contest/2133/problem/E

t = int(input())
from copy import deepcopy

from collections import Counter, defaultdict, deque

for _ in range(t):

    n = int(input())

    res = []
    conn = [[] for _ in range(n + 1)]
    deg = [0] * (n + 1)
    color = [[0, 0, 0] for _ in range(n + 1)]
    # g, y, b
    c = [0 for _ in range(n + 1)]
    vis = [False for _ in range(n + 1)]

    for _ in range(n - 1):
        a, b = map(int, input().split())
        conn[a].append(b)
        conn[b].append(a)
        deg[b] += 1
        deg[a] += 1

    deg2 = deepcopy(deg)

    stack = [i for i in range(2, n + 1) if deg[i] == 1]
    # vis[1] = True
    for s in stack:
        vis[s] = True

    while stack:

        cur = stack.pop()
        if color[cur][0] >= 3 or color[cur][1] >= 1:
            c[cur] = 2
        elif color[cur][0] == 2:
            c[cur] = 1
        else:
            c[cur] = 0

        for nxt in conn[cur]:
            # if vis[nxt]:
            #     continue
            color[nxt][c[cur]] += 1
            deg[nxt] -= 1
            if deg[nxt] == 1 and nxt != 1:
                vis[nxt] = True
                stack.append(nxt)

    if color[1][0] >= 3 or color[1][1] >= 1:
        c[1] = 2
    elif color[1][0] == 2:
        c[1] = 1
    else:
        c[1] = 0

    for i in range(1, n + 1):
        if c[i] == 2:
            res.append([2, i])
            res.append([1, i])
            deg2[i] = -1
            for nxt in conn[i]:
                deg2[nxt] -= 1

    for i in range(1, n + 1):
        if deg2[i] == -1 or c[i] > 0 or deg2[i] > 1:
            continue
        cur = i
        while True:
            f = 0
            res.append([1, cur])
            deg2[cur] = -1
            for nxt in conn[cur]:
                if deg2[nxt] >= 0:
                    cur = nxt
                    f = 1
                    break
            if f == 0:
                break


    print(len(res))

    for a,b in res:
        print(str(a) + ' ' + str(b))
