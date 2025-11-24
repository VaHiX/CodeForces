# Problem: CF 1948 G - MST with Matching
# https://codeforces.com/contest/1948/problem/G

"""
Algorithm: MST with Matching
Purpose: Find the minimum cost spanning tree where the cost includes both the sum of edge weights and the maximum matching in the tree multiplied by a constant c.

Approach:
1. Generate all edges of the graph with their weights.
2. Iterate through all possible subsets of vertices (using bitmask).
3. For each subset, compute the minimum spanning tree using Union-Find.
4. Calculate the total cost as the sum of edge weights plus the maximum matching size multiplied by c.
5. Keep track of the minimum cost found.

Time Complexity: O(2^n * n^2) where n <= 20
Space Complexity: O(n^2) for storing edges and Union-Find structure.
"""

def get_root(v, fa):
    # Path compression in Union-Find
    if fa[v] == v:
        return v
    fa[v] = get_root(fa[v], fa)
    return fa[v]


n, c = map(int, input().split())
e = [list(map(int, input().split())) for _ in range(n)]
# Generate list of edges with weights (excluding zero weights)
edge = [(e[i][j], i, j) for i in range(n) for j in range(i + 1, n) if e[i][j] > 0]
edge.sort()  # Sort edges by weight for MST-like processing
inf = float("inf")
ans = inf

# Iterate over all possible subsets of vertices using bitmask
for i in range(1, 1 << n):
    # Count number of vertices selected in this subset
    now = bin(i).count("1") * c  # Start with matching cost
    fa = list(range(n))  # Union-Find structure
    tot = n  # Number of connected components, starts with n
    for w, u, v in edge:
        # Early termination if current cost is already higher than best
        if now > ans:
            break
        # If both vertices are in the subset, process the edge
        if ((i >> u) & 1) or ((i >> v) & 1):
            u = get_root(u, fa)  # Find root of u
            v = get_root(v, fa)  # Find root of v
            if u == v:
                pass  # Skip if already connected
            else:
                fa[u] = v  # Union operation
                now += w  # Add edge weight to total
                tot -= 1  # Decrease number of components
    # If exactly one component, it's a valid spanning tree
    if tot == 1:
        ans = min(ans, now)

print(ans)


# https://github.com/VaHiX/CodeForces/