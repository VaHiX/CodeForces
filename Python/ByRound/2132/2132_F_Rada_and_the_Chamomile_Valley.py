# Contest 2132, Problem F: Rada and the Chamomile Valley
# URL: https://codeforces.com/contest/2132/problem/F

import sys

input = sys.stdin.readline
inf = 1 << 30
from collections import defaultdict, deque


def bridges(graph):
    """
    Iterative version to find all bridges in an undirected graph.
    Input: graph as adjacency list (graph[u] is a list of neighbors of u).
    Output: list of edges (u, v) that are bridges with u < v in each tuple.
    Time: O(V + E), Space: O(V)
    """
    n = len(graph)
    visited = [False] * n
    disc = [0] * n
    low = [0] * n
    timer = 0
    bridges = []

    # Use an explicit stack to simulate recursion.
    # Each stack frame: (u, parent, next_index_in_adjlist, parent_skip_remaining)
    for start in range(n):
        if visited[start]:
            continue

        # initialize the start node frame
        visited[start] = True
        disc[start] = low[start] = timer
        timer += 1
        stack = [(start, -1, 0, 0)]

        while stack:
            u, parent, idx, parent_skip = stack[-1]

            if idx < len(graph[u]):
                v = graph[u][idx]
                # update the next index in the current frame
                stack[-1] = (u, parent, idx + 1, parent_skip)

                # If this neighbor is the parent, skip exactly one occurrence (handles parallel edges)
                if v == parent and parent_skip > 0:
                    # decrement the remaining skip and continue
                    stack[-1] = (u, parent, idx + 1, parent_skip - 1)
                    continue

                if visited[v]:
                    # back-edge (or parallel edge treated as back-edge if parent was already skipped)
                    # update low[u] using discovery time of v
                    if disc[v] < low[u]:
                        low[u] = disc[v]
                else:
                    # tree edge: push child frame and initialize child discovery/low
                    visited[v] = True
                    disc[v] = low[v] = timer
                    timer += 1
                    # child should skip exactly one occurrence of its parent when scanning neighbors
                    stack.append((v, u, 0, 1))
            else:
                # finished exploring u
                stack.pop()
                if parent != -1:
                    # propagate low up to parent and check bridge condition
                    if low[u] < low[parent]:
                        low[parent] = low[u]
                    if low[u] > disc[parent]:
                        bridges.append((min(parent, u), max(parent, u)))

    return bridges


for i in range(int(input())):
    n, m = map(int, input().split())
    e = dict()
    for j in range(m):
        u, v = tuple(map(lambda x: int(x) - 1, input().split()))
        e[(min(u, v), max(u, v))] = j
    g = [[] for j in range(n)]
    for u, v in e:
        g[u].append(v)
        g[v].append(u)
    b = set(bridges(g))
    s, p = [0], [-1] * n
    vis = [0] * n
    vis[0] = 1
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                p[child] = parent
                s.append(child)
    path = [n - 1]
    while p[path[-1]] != -1:
        path.append(p[path[-1]])
    dp = [(inf, -1) for j in range(n)]
    s = set()
    vis = [0] * n
    for j in range(1, len(path)):
        u, v = min(path[j], path[j - 1]), max(path[j], path[j - 1])
        if ((u, v) in b) or ((v, u) in b):
            dp[u] = min(dp[u], (0, e[(u, v)]))
            dp[v] = min(dp[v], (0, e[(u, v)]))
            s.add(u)
            vis[u] = 1
            s.add(v)
            vis[v] = 1
    s = deque(s)
    f = max(vis)
    while s:
        parent = s.popleft()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                s.append(child)
            dp[child] = min(dp[child], (dp[parent][0] + 1, dp[parent][1]))
    out = []
    for j in range(int(input())):
        u = int(input())
        out.append(dp[u - 1][1] + 1 if f else -1)
    print(*out)
