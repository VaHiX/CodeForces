# Problem: CF 1738 D - Permutation Addicts
# https://codeforces.com/contest/1738/problem/D

"""
Code Purpose:
This code solves the problem of reconstructing a permutation 'a' and a threshold 'k' 
from a given sequence 'b'. The reconstruction is based on the rules defined in the 
problem description, which use the relationship between elements of 'a' and their 
positions to generate 'b'.

Algorithms/Techniques:
- Greedy reconstruction approach with BFS-like traversal
- Uses a tree-like structure to represent dependencies
- Reverses the process of generating 'b' from 'a' and 'k'

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by:
1. Determining the threshold 'k' based on how many elements in 'b' are greater than their index
2. Building a tree structure from the 'b' array where each node represents an element
3. Performing a traversal to reconstruct the permutation 'a'
"""

baku = []
for _ in range(int(input())):
    n = int(input())
    a = [int(t) - 1 for t in input().split()]  # Convert to 0-indexed

    # Determine threshold k as the number of elements in b that exceed their index
    k = sum(a[i] > i for i in range(n))
    baku.append([k])

    # Build a tree structure: child[x] contains all indices that are children of x
    child = [[] for _ in range(n + 1)]
    for i in range(n):
        x = a[i]
        if not 0 <= x < n:  # If x is out of valid range, set it to n
            x = n
        child[x].append(i)

    # BFS-like traversal starting from node n (the root)
    queue = [n]
    for a in queue:
        # Process all children of current node a
        for b in child[a]:
            if len(child[b]) == 0:  # If b has no children, add to queue
                queue.append(b)
        for b in child[a]:
            if len(child[b]) > 0:  # If b has children, add to queue
                queue.append(b)

    # Output permutation: skip the first element (root node) and convert back to 1-indexed
    baku.append([e + 1 for e in queue[1:]])

# Print all results
for b in baku:
    print(*b)


# https://github.com/VaHiX/CodeForces/