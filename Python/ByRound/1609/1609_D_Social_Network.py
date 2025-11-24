# Problem: CF 1609 D - Social Network
# https://codeforces.com/contest/1609/problem/D

"""
Purpose: This code solves the problem of determining the maximum number of acquaintances 
         (connected nodes in a graph) for any person after a sequence of introductions. 
         It uses Union-Find (Disjoint Set Union) data structure to manage the connected components.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression and union by size
- Iteratively process conditions and compute the maximum component size after each merge

Time Complexity: O(d * α(n)) where d is number of conditions, n is number of people, and α is inverse Ackermann function
Space Complexity: O(n) for the parent array in Union-Find structure
"""

n, d = map(int, input().split())
fa, remain = [-1] * (n + 1), 0  # 'fa' represents parent array for Union-Find, 'remain' tracks number of roots


def find(a):
    # Find root of node 'a' with path compression
    if fa[a] < 0:
        return a
    fa[a] = find(fa[a])  # Path compression
    return fa[a]


def merge(a, b):
    # Merge two sets
    a, b = find(a), find(b)
    if a == b:
        return 1  # Already in same set
    # Union by size: attach smaller tree under root of larger tree
    fa[a] += fa[b]  # Update size of root a
    fa[b] = a       # Set parent of b to a
    return 0


for _ in range(d):
    x, y = map(int, input().split())
    remain += merge(x, y)  # Perform merge operation and increment remain
    ans = 0
    b = sorted(fa)  # Sort the parent array to find the largest component sizes
    for i in range(remain + 1):
        if b[i] < 0:
            ans += b[i]  # Sum up the negative sizes (which represent the component sizes)
    print(-ans - 1)  # Convert back to positive and subtract 1 to get node count


# https://github.com/VaHiX/CodeForces/