# Problem: CF 2065 F - Skibidus and Slay
# https://codeforces.com/contest/2065/problem/F

"""
F. Skibidus and Slay
Algorithms/Techniques: Tree traversal, Sorting, Majority Element Detection
Time Complexity: O(n^2 * log(n)) in worst case due to sorting neighbors for each node
Space Complexity: O(n^2) for storing adjacency list and intermediate data structures

A tree is given with values on each vertex. For each value i from 1 to n,
we need to determine if there exists a non-trivial path such that i is the majority
of the values on that path (strictly more than floor(k/2) where k is the number of vertices in the path).

Approach:
- Build adjacency list representation of the tree.
- For each node, look at its neighbors and sort their values.
- Check if any value appears more than once in sorted neighbor values,
  which implies that value could be a majority in some path involving this node.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    h = list(map(int, input().split()))
    d = [[i] for i in range(n)]  # Adjacency list initialized with node indices
    for _ in range(n - 1):
        a, b = map(lambda x: int(x) - 1, input().split())  # Convert to 0-based indexing
        d[a].append(b)
        d[b].append(a)
    
    q = [0] * n  # Result array to store '1' or '0' for each value 1 to n
    
    for i in range(n):
        # Get values of all neighbors of node i
        w = sorted([h[j] for j in d[i]])
        
        # Check consecutive elements in sorted list for duplicates
        for j in range(len(w) - 1):
            if w[j] == w[j + 1]:
                q[w[j] - 1] = 1  # Mark that this value can be majority in some path
                
    print("".join(map(str, q)))


# https://github.com/VaHiX/codeForces/