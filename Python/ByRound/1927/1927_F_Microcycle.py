# Problem: CF 1927 F - Microcycle
# https://codeforces.com/contest/1927/problem/F

"""
Algorithm: Find the minimum weight edge in a simple cycle using Union-Find and BFS.
Approach:
1. Sort edges in descending order by weight.
2. Process edges one by one, using Union-Find to detect when adding an edge creates a cycle.
3. When a cycle is detected, store that edge as the minimum weight edge in the cycle.
4. Use BFS to reconstruct the cycle path from the graph built up to that point.
Time Complexity: O(m log m + n + m) where m is the number of edges and n is the number of vertices.
Space Complexity: O(n + m) for storing the graph and Union-Find structure.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def find(arr, a):
    li = []
    root = a
    while arr[root] != root:
        root = arr[root]
        li.append(root)
    for x in li:
        arr[x] = root
    return root


for _ in range(int(input())):
    n, m = map(int, input().split())

    arr = [i for i in range(n)]
    edges = []
    for _ in range(m):
        a, b, w = map(int, input().split())
        edges.append((a - 1, b - 1, w))

    edges.sort(key=lambda x: x[2], reverse=True)

    min_edge = None

    g = [[] for _ in range(n)]

    for edge in edges:
        a, b, w = edge
        pa = find(arr, a)
        pb = find(arr, b)
        arr[pa] = pb

        if pa == pb:
            # If both nodes are already in the same component, adding this edge forms a cycle
            min_edge = edge
        else:
            # Otherwise, we connect them in the graph
            g[a].append(b)
            g[b].append(a)

    start, end, min_w = min_edge
    v = [-1] * n
    v[start] = n  # Marking start as visited with a sentinel value
    q = [start]
    while len(q) > 0:
        t = []
        for curr in q:
            for neigh in g[curr]:
                if v[neigh] == -1:
                    v[neigh] = curr
                    t.append(neigh)
        q = t

    path = []
    c = end
    while c != n:
        path.append(c)
        c = v[c]

    print(min_w, len(path))
    print(*[x + 1 for x in path])


# https://github.com/VaHiX/CodeForces/