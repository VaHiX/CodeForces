# Contest 2107, Problem D: Apple Tree Traversing
# URL: https://codeforces.com/contest/2107/problem/D

from array import array
import sys

input = sys.stdin.readline

import heapq

t = int(input())
for _ in range(t):
    n = int(input())
    p = [array("i", []) for i in range(n + 1)]
    ans = []
    for i in range(n - 1):
        u, v = list(map(int, input().split()))
        p[u].append(v)
        p[v].append(u)

    heitht = [()] * (n + 1)
    vis = [0] * (n + 1)
    pre = [0] * (n + 1)
    euler_point = []

    stack = [1]
    while len(stack) > 0:
        u = stack.pop()
        euler_point.append(u)
        # vis[u] = 1
        for v in p[u]:
            if v == pre[u]:
                continue
            pre[v] = u
            stack.append(v)

    point_max = [()] * (n + 1)

    def update(a):
        below_a = [heitht[v] for v in p[a] if v != pre[a] and vis[v] == 0]
        below_a.sort()

        if len(below_a) == 0:
            heitht[a] = (1, a)
            point_max[a] = (1, a, a)
            return
        elif len(below_a) == 1:
            h_v, v = below_a[0]
            heitht[a] = (h_v + 1, v)
            point_max[a] = (h_v + 1, max(a, v), min(a, v))
            return

        h_v1, v1 = below_a[-1]
        h_v2, v2 = below_a[-2]
        heitht[a] = (h_v1 + 1, v1)
        point_max[a] = (h_v1 + h_v2 + 1, max(v1, v2), min(v1, v2))

    heap = []
    for u in reversed(euler_point):
        update(u)
        x, y, z = point_max[u]
        heapq.heappush(heap, (-x, -y, -z, u))

    seg = []

    while len(heap) > 0:
        d, u, v, a = heapq.heappop(heap)
        d, u, v = -d, -u, -v

        if vis[a]:
            continue
        if (d, u, v) != point_max[a]:
            continue

        seg.append((d, u, v))

        for now in (u, v):
            while now != a:
                vis[now] = 1
                now = pre[now]
        vis[a] = 1

        now = pre[a]
        while now and vis[now] == 0:  # 注意切断，这里可能退化为n^2
            update(now)
            heapq.heappush(
                heap, (-point_max[now][0], -point_max[now][1], -point_max[now][2], now)
            )
            now = pre[now]

    seg.sort()

    for i in range(len(seg) - 1, -1, -1):
        for x in seg[i]:
            print(x, end=" ")
    print()


"""
5
5
1 2
2 3
3 4
4 5
"""
