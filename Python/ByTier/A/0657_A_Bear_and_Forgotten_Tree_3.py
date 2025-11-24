# Problem: CF 657 A - Bear and Forgotten Tree 3
# https://codeforces.com/contest/657/problem/A

"""
Purpose: 
    This code attempts to reconstruct a tree given three parameters: 
    n (number of vertices), d (diameter), and h (height when rooted at vertex 1).
    
    The algorithm works by constructing a path of length d, then attaching additional 
    vertices to form the required height and structure, ensuring the diameter and 
    height constraints are satisfied.

Algorithms/Techniques:
    - Greedy tree construction based on diameter and height constraints.
    - Special cases handling for impossible combinations.
    
Time Complexity: O(n)
    - The algorithm constructs the tree by iterating through a linear number of edges (n - 1).
    
Space Complexity: O(1)
    - Only a constant amount of extra space is used, not counting the output storage.

"""

n, h, d = map(int, input().split())

# Check if the given parameters are valid for a tree
# h < d: height cannot be less than diameter (impossible)
# n < h + 1: number of vertices must be at least height + 1 (tree needs at least h+1 vertices to have height h)
# h > 2 * d: height cannot exceed twice the diameter (constraints of tree geometry)
# h == d == 1 and n > 2: if diameter and height are both 1, only 2 vertices are allowed, otherwise it's invalid
if h < d or n < h + 1 or h > 2 * d or h == d == 1 and n > 2:
    print(-1)
else:
    # First, create a path from 1 to d+1 (this establishes the diameter)
    for i in range(1, d + 1):
        print(i, i + 1)
    
    # If height is greater than diameter, we need to extend the tree further
    if h > d:
        # Connect the first vertex to a new vertex at position d+2 to create height h
        print(1, d + 2)
        # Continue extending the tree upward from d+2 to h
        for i in range(d + 2, h + 1):
            print(i, i + 1)
        # Attach remaining vertices to vertex 1 to ensure all vertices are included
        for i in range(h + 2, n + 1):
            print(1, i)
    else:
        # If height equals diameter, we simply connect the remaining vertices to vertex 2
        for i in range(d + 2, n + 1):
            print(i, 2)


# https://github.com/VaHiX/CodeForces/