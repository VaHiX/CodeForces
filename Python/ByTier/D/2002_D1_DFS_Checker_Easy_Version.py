# Problem: CF 2002 D1 - DFS Checker (Easy Version)
# https://codeforces.com/contest/2002/problem/D1

"""
D1. DFS Checker (Easy Version)

Purpose:
This code determines whether a given permutation of vertices in a perfect binary tree represents a valid Depth-First Search (DFS) order. For each query, it swaps two elements in the permutation and checks if the resulting sequence can be a DFS traversal.

The algorithm uses a special structure for a perfect binary tree to efficiently compute parent-child relationships and then verifies conditions based on the idea that in a valid DFS order, each node's value must be at most half of its parent's value (under specific indexing), which ensures that a DFS traversal is possible from that node upwards and downward.

Algorithms/Techniques:
- Perfect Binary Tree Construction using bit-lengths and index mapping
- Preprocessing to check "validity" conditions for DFS
- Efficient query handling with partial updates

Time Complexity: O(n + q * sqrt(n))
Space Complexity: O(n)

Note:
The tree is represented implicitly via its parent relationships.
Each node's children are determined using binary indexing (child1 = i+1, child2 = i + 2^(k - level[i]))
Valid DFS order condition: For each vertex i (except root), p[i] // 2 == p[parent[i]]
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n, q = map(int, input().split())
    _ = list(map(int, input().split()))
    p = list(map(int, input().split()))
    k = n.bit_length()  # Determine height of the perfect binary tree
    level = [-1] * n
    parent = [-1] * n
    child1 = [-1] * n
    child2 = [-1] * n
    level[0] = 1
    parent[0] = -1
    for i in range(n):
        if level[i] < k:
            child1[i] = i + 1  # First child
            child2[i] = i + 2 ** (k - level[i])  # Second child
            level[child1[i]] = level[child2[i]] = level[i] + 1
            parent[child1[i]] = parent[child2[i]] = i
    
    # ok[i] represents if the property holds for node i
    ok = [0] * n
    for i in range(n):
        if parent[i] != -1:
            ok[i] = int(p[i] // 2 == p[parent[i]])  # Property for valid DFS order

    sum_ok = sum(ok)  # Sum of all valid nodes
    ans = ["NO"] * q
    for i in range(q):
        x, y = map(lambda x: int(x) - 1, input().split())  # Convert to 0-indexed
        
        s = set()  # Set to store affected nodes
        
        if parent[x] != -1:
            s |= {x}  # Add node x to check
        if child1[x] != -1:
            s |= {child1[x], child2[x]}  # Add children of x to check
        if parent[y] != -1:
            s |= {y}  # Add node y to check
        if child1[y] != -1:
            s |= {child1[y], child2[y]}  # Add children of y to check
            
        # Update sum_ok by removing old values
        for j in s:
            sum_ok -= ok[j]
            ok[j] = 0

        # Simulate swap in permutation
        p[x], p[y] = p[y], p[x]

        # Update ok array and sum_ok based on the new values
        for j in s:
            ok[j] = int(p[j] // 2 == p[parent[j]])  # Update validity condition
            sum_ok += ok[j]
            
        if sum_ok == n - 1:  # N-1 valid nodes (except root)
            ans[i] = "YES"
    return "\n".join(ans)


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/