# Problem: CF 2143 C - Max Tree
# https://codeforces.com/contest/2143/problem/C

"""
C. Max Tree
Algorithms/Techniques: Topological Sorting, Greedy Approach on Tree

Time Complexity: O(n)
Space Complexity: O(n)

This problem asks to assign values 1..n to tree vertices such that the sum of edge contributions is maximized.
Each edge contributes x if p_u > p_v and y otherwise, where u < v.
The approach is to build a directed graph where:
- If x > y, we direct edge from v to u (favoring larger values at u)
- Else, we direct edge from u to v (favoring larger values at v)
Then perform topological sorting to assign positions: lower in topo-order gets smaller value.
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    adj = [[] for _ in range(n)]
    deg = [0] * n
    for _ in range(n - 1):
        u, v, x, y = map(int, input().split())
        u -= 1
        v -= 1
        assert u < v
        if x > y:
            adj[v].append(u)
            deg[u] += 1
        else:
            adj[u].append(v)
            deg[v] += 1
    Q = [v for v in range(n) if deg[v] == 0]
    p = [None] * n
    order = 0
    while Q:
        v = Q.pop()
        p[v] = order = order + 1
        for u in adj[v]:
            deg[u] -= 1
            if deg[u] == 0:
                Q.append(u)
    print(*p)


# https://github.com/VaHiX/codeForces/