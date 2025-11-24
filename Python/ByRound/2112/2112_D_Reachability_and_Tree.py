# Problem: CF 2112 D - Reachability and Tree
# https://codeforces.com/contest/2112/problem/D

"""
D. Reachability and Tree

Purpose:
This code determines whether a directed version of a given undirected tree can be constructed such that exactly n good ordered pairs (u, v) exist, where u can reach v in the directed graph. A good pair means there is a directed path from u to v.

Algorithms/Techniques:
- Tree traversal using BFS/DFS
- Edge orientation to satisfy reachability conditions
- Graph representation using adjacency lists
- Detecting presence of vertex with degree 2 (which affects possible orientations)

Time Complexity: O(n) per test case
Space Complexity: O(n) for storage of adjacency lists and auxiliary arrays

Input Format:
- First line contains number of test cases t.
- For each test case:
    - First line: n (number of vertices)
    - Next n-1 lines: pairs of integers representing edges

Output Format:
- For each test case, if solution exists:
    - print "YES"
    - print n-1 directed edges (each pair u v indicates u -> v)
- else print "NO"
"""

import sys

le = sys.__stdin__.read().split("\n")[::-1]  # Read all input and reverse it for efficient popping
af = []  # Store final results
for _ in range(int(le.pop())):  # Loop through each test case
    n = int(le.pop())  # Get number of nodes in this tree
    d = [0] * n  # Degree array to store degree of each node
    ar = [[] for _ in range(n)]  # Adjacency list representation of tree
    Bo = [True] * n  # Boolean array to track coloring during traversal (for orientation)
    nv = [True] * n  # Visited array to prevent revisiting nodes in BFS
    for _ in range(n - 1):  # Process all edges
        u, v = list(map(int, le.pop().split()))  # Read and parse edge
        u -= 1  # Convert to 0-based indexing
        v -= 1
        d[u] += 1  # Increase degree of u
        d[v] += 1  # Increase degree of v
        ar[u].append(v)  # Add v to adjacency list of u
        ar[v].append(u)  # Add u to adjacency list of v
    if 2 in d:  # If a node with degree 2 exists, orientation is possible
        af.append("YES")
        i = d.index(2)  # Find first node with degree 2
        pi = [0 if i != 0 else 1]  # Stack for BFS; initialize with root node
        while pi:  # BFS loop
            u = pi.pop()  # Pop current node
            nv[u] = False  # Mark as visited
            if u == i:  # If we hit the special node with degree 2
                Bo[i] = not (Bo[i])  # Flip the orientation flag for this node
            for v in ar[u]:  # Iterate neighbors of current node
                if nv[v]:  # If neighbor hasn't been visited
                    pi.append(v)  # Add neighbor to stack for later visits
                    x, y = u + 1, v + 1  # Convert back to 1-based indices
                    if Bo[u]:  # Based on orientation of current node
                        x, y = y, x  # Flip assignment of direction
                    Bo[v] = not (Bo[u])  # Assign opposite orientation to neighbor
                    af.append(str(x) + " " + str(y))  # Add directed edge to result
    else:
        af.append("NO")  # No node with degree 2 implies impossible orientation for n good pairs
print("\n".join(map(str, af)))  # Print all outputs


# https://github.com/VaHiX/codeForces/