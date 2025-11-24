# Problem: CF 1675 F - Vlad and Unfinished Business
# https://codeforces.com/contest/1675/problem/F
 
from collections import deque
 
I = lambda: int(input())
R = lambda: map(int, input().split())
for _ in range(I()):
    input()
    n, k = R()
    src, des = R()
    src, des = src - 1, des - 1
    task = [False] * n
    task[des] = True
    for i in R():
        task[i - 1] = True
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = R()
        u, v = u - 1, v - 1
        g[u].append(v)
        g[v].append(u)
 
    depth, parent = [0] * n, [-1] * n
    q, son = deque([src]), []
    while q:
        u = q.popleft()
        for v in g[u]:
            if v != parent[u]:
                q.append(v)
                son.append(v)
                depth[v], parent[v] = depth[u] + 1, u
 
    res = 0
    for u in son[::-1]:
        task[parent[u]] |= task[u]
        if task[u]:
            res += 2
    print(res - depth[des])
 
 
# https://github.com/VaHiX/CodeForces/