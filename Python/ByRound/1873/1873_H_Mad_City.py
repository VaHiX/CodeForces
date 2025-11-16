# Problem: CF 1873 H - Mad City
# https://codeforces.com/contest/1873/problem/H

"""
Algorithm: Determine if Valeriu can escape Marcel forever in a graph-based game.
Techniques: 
- Graph processing to identify cycle nodes using BFS (removing leaves iteratively)
- BFS from both starting positions to find distances to cycle nodes
- Compare distances to assess escape possibility

Time Complexity: O(n + m) where n is number of nodes and m is number of edges
Space Complexity: O(n + m) for adjacency list representation and tracking arrays
"""

import sys
from collections import deque

input = sys.stdin.readline


def can_escape(n, a, b, edges):
    # Build adjacency list and degree count
    g = [[] for _ in range(n + 1)]
    deg = [0] * (n + 1)
    for u, v in edges:
        g[u].append(v)
        g[v].append(u)
        deg[u] += 1
        deg[v] += 1
    
    # Identify nodes not on cycles by removing leaves iteratively
    q = deque()
    on_cycle = [True] * (n + 1)  # Initially all nodes are considered on cycle
    for i in range(1, n + 1):
        if deg[i] == 1:
            q.append(i)
            on_cycle[i] = False  # Leaf nodes are not on cycle
    
    # Remove leaves iteratively until only cycles remain
    while q:
        leaf = q.popleft()
        for nei in g[leaf]:
            if on_cycle[nei]:
                deg[nei] -= 1
                if deg[nei] == 1:
                    on_cycle[nei] = False
                    q.append(nei)
    
    # BFS from Valeriu's position to find nearest cycle node
    dist_b = [-1] * (n + 1)
    qb = deque([b])
    dist_b[b] = 0
    meet = -1  # Target node to meet at (first cycle node encountered)
    while qb:
        u = qb.popleft()
        if on_cycle[u]:
            meet = u
            break
        for v in g[u]:
            if dist_b[v] == -1:
                dist_b[v] = dist_b[u] + 1
                qb.append(v)
    
    # BFS from Marcel's position to find distance to the same target node, if possible
    dist_a = [-1] * (n + 1)
    qa = deque([a])
    dist_a[a] = 0
    while qa and dist_a[meet] == -1:  # Continue while not reached meet node
        u = qa.popleft()
        for v in g[u]:
            if dist_a[v] == -1:
                dist_a[v] = dist_a[u] + 1
                qa.append(v)
    
    # If Valeriu can reach the meeting point before or at same time as Marcel, he escapes
    return dist_b[meet] < dist_a[meet]


def main():
    t = int(input())
    out = []
    for _ in range(t):
        n, a, b = map(int, input().split())
        edges = [tuple(map(int, input().split())) for _ in range(n)]
        out.append("YES" if can_escape(n, a, b, edges) else "NO")
    print("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/