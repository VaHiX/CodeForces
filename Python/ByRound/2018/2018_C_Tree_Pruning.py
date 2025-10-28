# Problem: CF 2018 C - Tree Pruning
# https://codeforces.com/contest/2018/problem/C

"""
Problem: Tree Pruning
Algorithm: 
    - Build adjacency list representation of a tree
    - Perform BFS to get distances from root and parent relationships
    - Use DFS to calculate subtree sizes
    - Identify nodes that are "heavy" (largest subtree) in each branch
    - Perform Euler tour to process tree in DFS order
    - Use LCA (Lowest Common Ancestor) technique to track leaf distances
    - Count minimum operations to make all leaves at same distance

Time Complexity: O(n) per test case, where n is number of nodes
Space Complexity: O(n) for storing graph, distance, parent, and auxiliary arrays

The code uses a complex data structure approach with BFS, DFS, and Euler Tour
to efficiently compute the number of operations needed.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    # Create an adjacency list representation of the graph
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = map(int, input().split())
        s[u + 2] += 1
        s[v + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * (2 * m)
    for i in range(2 * m):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


def bfs(s):
    # Performs BFS to compute distance from root and parent array
    q = [s]
    dist = [inf] * (n + 1)
    dist[s] = 0
    parent = [-1] * (n + 1)
    for i in q:
        di = dist[i]
        # Iterate through neighbors of node i
        for v in range(s0[i], s0[i + 1]):
            j = G[v]
            if dist[j] == inf:
                q.append(j)
                dist[j] = di + 1
                parent[j] = i
    return q, dist, parent


def lca(u, v):
    # Compute Lowest Common Ancestor of nodes u and v
    while z[u] ^ z[v]:
        if dist[z[u]] >= dist[z[v]]:
            u = parent[z[u]]
        else:
            v = parent[z[v]]
    ans = u if dist[u] <= dist[v] else v
    return ans


def euler_tour(s):
    # Perform Euler tour to visit nodes in DFS order
    st = [s]
    now = list(s0)
    t = 0
    t1 = [-1] * (n + 1)
    e = [0] * n
    while st:
        i = st[-1]
        if t1[i] == -1:
            t1[i], e[t] = t, i
            t += 1
        while now[i] ^ s0[i + 1] and t1[G[now[i]]] ^ -1:
            now[i] += 1
        if now[i] == s0[i + 1]:
            st.pop()
        else:
            st.append(G[now[i]])
            now[i] += 1
    return e


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n = int(input())
    G, s0 = make_graph(n, n - 1)
    p, dist, parent = bfs(1)
    cnt = [1] * (n + 1)
    # Compute subtree sizes 
    for i in p[::-1][:-1]:
        cnt[parent[i]] += cnt[i]
    z = [i for i in range(n + 1)]
    # Identify heaviest subtrees
    for i in p:
        j, ma, di = i, -1, dist[i]
        for v in range(s0[i], s0[i + 1]):
            k = G[v]
            if dist[k] < di:
                continue
            if ma < cnt[k]:
                j, ma = k, cnt[k]
        z[j] = z[i]
    e = euler_tour(1)
    la = [1] * (n + 1)
    ans0 = [n - 1] * (n + 1)
    # Compute answer using Euler tour and LCA
    for i in e[1:]:
        j = dist[i]
        ans0[j] -= j - dist[lca(i, la[j])]
        la[j] = i
    ans1 = min(ans0)
    ans.append(ans1)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/