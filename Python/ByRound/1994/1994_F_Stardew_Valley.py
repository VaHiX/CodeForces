# Problem: CF 1994 F - Stardew Valley
# https://codeforces.com/contest/1994/problem/F

"""
Problem: Stardew Valley
Purpose: Find a Eulerian cycle in a graph that includes all edges with NPCs (c=1).
This is a variation of finding an Eulerian Path/Cycle, where we must traverse 
each NPC-containing edge exactly once and return to the starting vertex.

Algorithm:
1. Identify edges with NPCs and construct a graph with only NPC edges.
2. Check if such a cycle exists:
   - Each vertex in the subgraph formed by NPC edges must have even degree.
3. If valid, use Hierholzer's algorithm to find Eulerian cycle:
   - Start DFS from any vertex.
   - Use a stack to store the current path.
   - When a vertex is dead-end, add it to the result.
   - Reverse the result to get the correct order.

Time Complexity: O(n + m) - Linear time for graph traversal and Eulerian cycle construction.
Space Complexity: O(n + m) - Space for adjacency list representation and auxiliary arrays.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to encode two values into one integer
    return u << 20 ^ v


def make_graph(n, m):
    # Build adjacency list for the graph composed of NPC edges
    s = [0] * (n + 3)
    for i in range(m):
        if not now[i]:
            continue
        s[e[i << 1 ^ 0] + 2] += 1
        s[e[i << 1 ^ 1] + 2] += 1
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * (s[-1] << 1)
    for i in range(m << 1):
        if not now[i >> 1]:
            continue
        j = e[i] + 1
        G[s[j]] = f(e[i ^ 1], i >> 1)  # Store neighbor and edge index
        s[j] += 1
    return G, s


def bfs(s):
    # BFS to determine if vertices are connected via NPC edges
    q, color[s] = [s], 0
    for i in q:
        for v in range(s0[i], s0[i + 1]):
            j, c = G[v] >> 20, G[v] & 0xFFFFF
            if color[j] == -1:
                q.append(j)
                color[j] = c
    return q


t = int(input())
ans = []
for _ in range(t):
    n, m = map(int, input().split())
    e, now, dp = [0] * (m << 1), [0] * m, [0] * (n + 1)
    for i in range(m):
        u, v, c = map(int, input().split())
        e[i << 1], e[i << 1 ^ 1] = u, v
        if c:
            dp[u] ^= 1
            dp[v] ^= 1
        else:
            now[i] = 1
    G, s0 = make_graph(n, m)
    color = [-1] * (n + 1)
    for i in range(m):
        now[i] ^= 1
    ans0 = "YES"
    for s in range(1, n + 1):
        if color[s] ^ -1:
            continue
        p = bfs(s)
        for i in p[::-1][:-1]:
            c = color[i]
            now[c] = dp[i]
            dp[i ^ e[c << 1] ^ e[c << 1 ^ 1]] ^= dp[i]
        if dp[s]:
            ans0 = "NO"
            break
    ans.append(ans0)
    if ans0 == "NO":
        continue
    G, s0 = make_graph(n, m)
    s1, k = list(s0), s0[-1] >> 1
    ans0, st, l = [0] * (k + 1), [1], 0
    while st:
        i = st[-1]
        while s1[i] ^ s0[i + 1] and not now[G[s1[i]] & 0xFFFFF]:
            s1[i] += 1
        if s1[i] == s0[i + 1]:
            ans0[l] = st.pop()
            l += 1
            continue
        now[G[s1[i]] & 0xFFFFF] = 0
        st.append(G[s1[i]] >> 20)
    ans.append(str(k))
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/