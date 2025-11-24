# Problem: CF 1764 C - Doremy's City Construction
# https://codeforces.com/contest/1764/problem/C

"""
Algorithm: 
- The problem is about constructing a graph with maximum edges under a constraint:
  No three vertices u, v, w such that a_u <= a_v <= a_w and edges (u,v) and (v,w) exist.
- This means the graph must be free of a specific type of induced subgraph (a "path" with increasing altitudes).
- Key insight:
  - Sort vertices by altitude.
  - For a sorted sequence, if we choose a vertex v and connect it to all vertices with lower altitude and all with higher altitude,
    it forms a "complete bipartite" structure.
  - The maximum number of edges is achieved by choosing a cut in the sorted array such that:
    - Left part: all vertices with smaller altitude
    - Right part: all vertices with greater altitude
  - For a cut at position i (0-based in the sorted array), number of edges = i * (n - i)
  - We iterate over all valid cuts (where altitude changes) and compute the maximum.

Time Complexity: O(n log n) due to sorting, where n is the number of vertices.
Space Complexity: O(n) for storing and sorting the array of altitudes.
"""

for i in range(int(input())):
    n = int(input())
    L = sorted(list(map(int, input().split())))
    print(
        max([i * (n - i) for i in range(1, len(L)) if L[i] != L[i - 1]], default=n // 2)
    )


# https://github.com/VaHiX/CodeForces/