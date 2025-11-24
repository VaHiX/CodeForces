# Problem: CF 2110 E - Melody
# https://codeforces.com/contest/2110/problem/E

"""
E. Melody

Purpose:
This code determines whether a sequence of sounds can form a beautiful, non-boring melody, 
where each sound is used exactly once. A melody is considered beautiful if consecutive sounds 
differ in only volume or only pitch. It is boring if any three consecutive sounds share the same 
volume or pitch.

Algorithm:
- This problem is modeled as finding an Eulerian Path in a graph where:
    - Nodes represent unique volumes and pitches.
    - Edges represent sounds (with volume and pitch).
- The approach involves:
    1. Mapping volume and pitch values to indices for graph representation.
    2. Building adjacency lists based on sound connections.
    3. Checking if the graph has an Eulerian path or cycle by validating odd-degree nodes.
    4. Performing a DFS-based Hierholzer's algorithm to reconstruct the path.

Time Complexity: O(n), where n is the number of sounds, due to linear processing of edges and nodes.
Space Complexity: O(n), for storing mappings, adjacency lists, and auxiliary data structures.

Techniques:
- Graph representation using adjacency lists
- Eulerian path detection and reconstruction using Hierholzer's algorithm
- Union-Find or node mapping with hashmaps for efficient indexing
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    visit = [0] * n
    mapv = {}
    cv = 0
    mapp = {}
    cp = 0
    edge = []
    for i in range(n):
        vi, pi = map(int, input().split())
        vi = mapv.setdefault(vi, cv)  # Map volume to index if not already mapped
        if vi == cv:
            cv += 1  # Increment count of unique volumes
        pi = mapp.setdefault(pi, cp)  # Map pitch to index if not already mapped
        if pi == cp:
            cp += 1  # Increment count of unique pitches
        edge += [(vi, pi)]
    
    node = [[] for _ in range(cv + cp)]  # Adjacency list for the graph
    for i, e in enumerate(edge):
        vi, pi = e
        node[vi] += [i]  # Connect volume to sound index
        node[pi + cv] += [i]  # Connect pitch to sound index (shifted by volume count)
    
    edge = [(vi, pi + cv) for vi, pi in edge]  # Update edges to point to graph nodes
    cv = cv + cp  # Total number of unique volume/pitch nodes
    
    vodd = []  # List of nodes with odd degree
    fail = False
    for i in range(cv):
        if len(node[i]) % 2 == 1:
            vodd += [i]
    
    if len(vodd) > 2:
        print("NO")
        continue
    
    cnode = vodd[1] if vodd else 0  # Start node for DFS (first odd-degree or 0)
    o = []
    visit = [0] * n
    edgeleft = [len(node[i]) for i in range(cv)]  # Track remaining edges per node
    
    stack = [(-1, cnode)]
    while stack:
        prve, v = stack[-1]
        if edgeleft[v]:  # Still edges to traverse from this node
            e = node[v].pop()  # Get next edge
            if visit[e]:
                continue
            visit[e] = 1
            a, b = edge[e]
            edgeleft[a] -= 1
            edgeleft[b] -= 1
            next_node = a if a != v else b
            stack.append((e, next_node))
        else:
            stack.pop()
            if prve != -1:
                o += [prve + 1]  # Add sound index to output sequence
    
    if len(o) != n:
        print("NO")
    else:
        print("YES")
        print(*o)


# https://github.com/VaHiX/codeForces/