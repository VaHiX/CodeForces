# Problem: CF 2127 H - 23 Rises Again
# https://codeforces.com/contest/2127/problem/H

"""
H. 23 Rises Again

Purpose:
This code solves a problem involving finding the maximum number of edges in a "candy" subgraph of a given graph.
A candy graph is defined as a graph where every vertex has degree at most 2.
The algorithm attempts to construct such a graph by iteratively selecting or modifying edges using randomization and greedy strategies.

Algorithms/Techniques:
- Randomized greedy approach with backtracking (via rejection sampling)
- Degree-based edge selection and modification
- Graph representation using adjacency lists

Time Complexity: O(n^2 * NUM) per test case, where NUM is a fixed large constant (10000),
                 and n is the number of vertices. In practice, this is efficient for small n (≤30).

Space Complexity: O(n + m), where n is the number of vertices and m is the number of edges.
                  This includes storage for adjacency lists, degrees, and edge information.

Input:
- Multiple test cases
- For each test case:
  - Two integers n and m representing vertices and edges
  - m lines containing pairs of integers u, v indicating an edge

Output:
- Maximum number of edges in a candy subgraph
"""

import random
import sys
from collections import defaultdict

input = sys.stdin.readline
P = 998244353
random.seed(P)


def solve():
    n, m = map(int, input().split())
    deg = [0] * (n + 1)  # Degree of each vertex
    G = defaultdict(list)  # Adjacency list representation
    E = []  # List of all edges
    chs = [0] * m  # Tracks whether an edge is selected
    for _ in range(m):
        u, v = map(int, input().split())
        E.append((u, v))
    NUM = 10000
    TRY = n * n * NUM  # Number of iterations for randomization
    ans = 0
    for _ in range(TRY):
        id = random.randint(0, m - 1)  # Pick a random edge index
        if chs[id]:
            continue  # Skip if already selected
        u, v = E[id]
        # Check if both endpoints have degree < 2 (can add this edge)
        if deg[u] == 2 and deg[v] == 2:
            continue  # Skip adding to avoid exceeding max degree 2
        if deg[u] < 2 and deg[v] < 2:
            # Add the edge
            deg[u] += 1
            deg[v] += 1
            chs[id] = 1
            ans += 1
            G[u].append((v, id))  # Append neighbor and edge ID
            G[v].append((u, id))
        else:
            # One or both of the vertices have degree >= 2
            if deg[v] == 2:
                u, v = v, u  # Ensure u has degree 2
            assert deg[v] < 2
            assert deg[u] == 2
            pos = random.randint(0, 1)
            # Swap an existing edge to avoid violating degree constraints
            if len(G[u]) < 2:
                continue  # Not enough edges to modify
            G[u][pos], G[u][1] = G[u][1], G[u][pos]  # Swap edges in adjacency list
            ov, oid = G[u][1]  # Get the old neighbor and its edge ID
            # Update the old neighbor's adjacency list
            if G[ov][0][1] == oid:
                G[ov][0], G[ov][-1] = G[ov][-1], G[ov][0]  # Swap to move removed edge
            G[ov].pop()  # Remove the last element
            deg[u] -= 1
            deg[ov] -= 1
            chs[oid] = 0  # Mark old edge as unselected
            G[u].pop()  # Remove from adjacency list
            deg[u] += 1
            deg[v] += 1
            chs[id] = 1  # Mark new edge as selected
            G[u].append((v, id))
            G[v].append((u, id))
    print(ans)


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/