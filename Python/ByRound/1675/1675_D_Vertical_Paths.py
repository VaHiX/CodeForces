# Problem: CF 1675 D - Vertical Paths
# https://codeforces.com/contest/1675/problem/D
 
"""
Code Purpose:
This code solves the problem of finding the minimum number of vertical paths in a rooted tree such that 
each vertex belongs to exactly one path, and paths go down from parent to child. 
The algorithm uses a greedy approach to construct paths by traversing from leaves up to the root, 
avoiding reprocessing vertices already part of a path. 
 
Algorithms/Techniques:
- Greedy approach to build paths
- Tree traversal from leaves to root
- Set-based tracking of unvisited nodes
 
Time Complexity: O(n) - Each node is visited at most once, and operations are linear.
Space Complexity: O(n) - For storing parent array, visited array, and result paths.
"""
 
I = lambda: int(input())
for _ in range(I()):
    n = I()
    p = [int(i) - 1 for i in input().split()]  # Convert to 0-based indexing
 
    # Set of all parents (vertices with at least one child)
    s, v, a = set(p), [1] * (n), []
    
    # Iterate through each vertex
    for i in range(n):
        # Skip if this vertex is a parent (has children), unless it's the root
        if i in s and n > 1:
            continue
        # Build a path from current vertex up to root
        t = []
        while v[i]:  # While vertex is not yet visited
            t += [i + 1]  # Add vertex to path (convert back to 1-based)
            v[i] = 0  # Mark as visited
            i = p[i]  # Move to parent
        a += [t[::-1]]  # Reverse path to get it from root to leaf
 
    print(len(a))  # Print number of paths
    for v in a:  # For each path
        print(len(v))  # Print its length
        print(*v)  # Print vertices in path
 
 
# https://github.com/VaHiX/CodeForces/