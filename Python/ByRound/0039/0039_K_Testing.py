# Contest 39, Problem K: Testing
# URL: https://codeforces.com/contest/39/problem/K

import os, sys

if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "rt")
I = sys.stdin.readline

n, m, k = map(int, I().split())
a = []
for _ in range(n):
    a.append(I().rstrip())

from collections import deque


def serch(i, j):
    global n, m
    que = deque()
    que.append((i, j))
    vis[i][j] = 1
    maxu, maxv = 0, 0
    while que:
        u, v = que.popleft()
        maxu, maxv = max(maxu, u), max(maxv, v)
        if u > 0 and a[u - 1][v] == "*" and not vis[u - 1][v]:
            que.append((u - 1, v))
            vis[u - 1][v] = 1
        if v > 0 and a[u][v - 1] == "*" and not vis[u][v - 1]:
            que.append((u, v - 1))
            vis[u][v - 1] = 1
        if u < n - 1 and a[u + 1][v] == "*" and not vis[u + 1][v]:
            que.append((u + 1, v))
            vis[u + 1][v] = 1
        if v < m - 1 and a[u][v + 1] == "*" and not vis[u][v + 1]:
            que.append((u, v + 1))
            vis[u][v + 1] = 1
    return (i, j, maxu, maxv)


obj = []
vis = [[0] * m for _ in range(n)]
for i in range(n):
    for j in range(m):
        if a[i][j] == "*" and not vis[i][j]:
            obj.append(serch(i, j))


def segment(t, b):
    global m
    seg1 = []
    for o in obj:
        if o[0] >= t and o[2] <= b:
            seg1.append((o[1], o[3], 1))
        if (o[0] < t and o[2] >= t) or (o[0] <= b and o[2] > b):
            seg1.append((o[1], o[3], 5))
    seg1.sort()

    seg2 = []
    for s in seg1:
        if not seg2 or s[0] > seg2[-1][1]:
            seg2.append(s)
        else:
            l, r, num = seg2.pop()
            seg2.append((l, max(r, s[1]), num + s[2]))

    seg3 = []
    if not seg2:
        seg3 = [(0, m - 1, 0)]
    else:
        if seg2[0][0] > 0:
            seg3.append((0, seg2[0][0] - 1, 0))
        seg3.append(seg2[0])
        for s in seg2[1:]:
            if s[0] > seg3[-1][1]:
                seg3.append((seg3[-1][1] + 1, s[0] - 1, 0))
            seg3.append(s)
        if seg3[-1][1] < m - 1:
            seg3.append((seg3[-1][1] + 1, m - 1, 0))
    return seg3


def cover(seg):
    ans = 0
    k = len(seg)
    for i in range(k):
        num = seg[i][2]
        if num > 3:
            continue
        if num == 0:
            l = seg[i][1] - seg[i][0] + 1
            r = 0
        else:
            l = 1
            r = 1
        j = i + 1
        while j < k:
            num += seg[j][2]
            if num > 3:
                break
            if seg[j][2] > 0:
                r += 1
            else:
                r += seg[j][1] - seg[j][0] + 1
            j += 1
        ans += l * r
    return ans


out = 0
y = []
for o in obj:
    y += [o[0], o[2]]
y = sorted(set(y))
k = len(y)
y.append(n)
last = -1
for i in range(k):
    cnt = 0
    for j in range(i, k):
        seg = segment(y[i], y[j])
        cnt += cover(seg) * (y[j + 1] - y[j])
    out += cnt * (y[i] - last)
    last = y[i]

print(out)
