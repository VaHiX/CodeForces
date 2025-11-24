# Problem: CF 1387 A - Graph
# https://codeforces.com/contest/1387/problem/A

"""
Algorithm: This solution uses a graph coloring and linear system solving approach.
It treats each connected component of the graph separately and assigns variables 
to nodes based on a bipartite-like structure. For each connected component,
it attempts to solve a system of linear equations with constraints derived
from the edge weights. It uses BFS to traverse and assign values, checking 
consistency of the system.

Time Complexity: O(N + M) where N is number of nodes and M is number of edges.
Space Complexity: O(N + M) for storing the graph and auxiliary arrays.
"""

from sys import stdin

input = stdin.readline
n, m = map(int, input().split())
g = [[] for _ in range(n)]
for _ in range(m):
    u, v, w = map(int, input().split())
    u -= 1
    v -= 1
    # Multiply weight by 2 to avoid fractional operations in the logic
    g[u].append((w * 2, v))
    g[v].append((w * 2, u))
vis = [0] * n
val = [0] * n
k = [0] * n
b = [0] * n
for i in range(n):
    if vis[i]:
        continue
    q = [i]
    vis[i] = 1
    x = 0
    nx = 0
    k[i] = 1
    t = 0
    while t < len(q):
        u = q[t]
        t += 1
        for w, v in g[u]:
            if not vis[v]:
                # Mark node as visited, set its coefficient and constant term
                vis[v] = 1
                k[v] = -k[u]  # Flip sign as we're moving to a new level
                b[v] = w - b[u]  # Compute constant term
                q.append(v)
            elif nx:
                # Check consistency with previously assigned values
                if k[u] * x + b[u] + k[v] * x + b[v] != w:
                    print("NO")
                    exit()
            else:
                # If it's the first time seeing a conflicting node
                if k[u] == -k[v]:
                    # Check if assignment is consistent with constraints
                    if b[u] + b[v] == w:
                        continue
                    else:
                        print("NO")
                        exit()
                nx = 1
                # Compute value of x by solving linear equation
                x = (w - b[u] - b[v]) // (k[u] + k[v])
    if not nx:
        # If no conflict occurred, find median value among computed terms
        ps = [-k[i] * b[i] for i in q]
        ps.sort()
        x = ps[len(ps) // 2]
    # Assign final values to nodes in current component
    for i in q:
        val[i] = k[i] * x + b[i]
print("YES")
# Output the values scaled back by 2 (since we multiplied earlier)
print(*[i / 2 for i in val])


# https://github.com/VaHiX/CodeForces/