"""
Problem: CF2131D - Arboris Contractio

This program solves a tree problem where we need to find the minimum number of edges
to remove so that all remaining connected components are stars (trees with diameter at most 2).

Approach:
1. The problem reduces to finding the maximum number of star centers in the tree.
2. A star center is a node connected to multiple leaves.
3. The answer is (number of leaves - maximum number of leaves connected to any single node).

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the tree
"""

import sys
from collections import defaultdict

def solve():
    """
    Solves a single test case for the Arboris Contractio problem.
    Reads the tree and prints the minimum number of edges to remove.
    """
    n = int(sys.stdin.readline())
    
    # Special case: tree with 2 nodes (single edge)
    if n == 2:
        print(0)
        return
    
    # Build adjacency list
    adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = map(int, sys.stdin.readline().split())
        adj[u].append(v)
        adj[v].append(u)
    
    # Count how many leaves are connected to each node
    leaf_count = [0] * (n + 1)
    
    # Find all leaves (nodes with only one connection)
    for node in range(1, n + 1):
        if len(adj[node]) == 1:  # This is a leaf
            # The only connection is to its parent
            parent = adj[node][0]
            leaf_count[parent] += 1
    
    # The answer is (total_leaves - max_leaves_connected_to_any_node)
    total_leaves = sum(leaf_count)
    max_leaves = max(leaf_count) if leaf_count else 0
    
    print(total_leaves - max_leaves)

def main():
    """Main function to handle multiple test cases."""
    t = int(sys.stdin.readline())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()
