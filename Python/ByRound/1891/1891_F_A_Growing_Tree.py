# Problem: CF 1891 F - A Growing Tree
# https://codeforces.com/contest/1891/problem/F

"""
Problem: F. A Growing Tree
Algorithm: Tree traversal with Fenwick Tree for range updates and queries
Time Complexity: O(q log q) per test case, where q is the number of queries
Space Complexity: O(q) for storing the tree structure and updates

This solution handles a dynamic tree where:
1. Vertices can be added as children (type 1 queries)
2. Values can be added to all nodes in a subtree (type 2 queries)

The approach uses:
- A Fenwick Tree (Binary Indexed Tree) to efficiently handle range updates
- A depth-first traversal to process updates in the correct order
- Preprocessing to build the tree structure and store updates
"""

import sys
from bisect import *
from collections import *
from heapq import *
from itertools import *
from random import *

input = sys.stdin.readline

d4 = (1, 0), (0, 1), (-1, 0), (0, -1)
d8 = (1, 1), (1, 0), (1, -1), (0, 1), (0, -1), (-1, 1), (-1, 0), (-1, -1)
alpha = "abcdefghijklmnopqrstuvwxyz"
mod1 = 10**9 + 7
mod2 = 998244353


class FenwickTree:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)  # Fenwick tree initialized to 0

    def update(self, index, value):
        """Add 'value' to index 'index' in the Fenwick tree"""
        while index <= self.size:
            self.tree[index] += value
            index += index & -index

    def query(self, index):
        """Returns the sum of the range [1, index]"""
        sum = 0
        while index > 0:
            sum += self.tree[index]
            index -= index & -index
        return sum

    def range_query(self, left, right):
        """Returns the sum of the range [left, right]"""
        return self.query(right) - self.query(left - 1)


class UnionFind:
    def __init__(self, n):
        self.parent = [-1] * n
        self.size = [1] * n

    def find(self, node):
        while self.parent[node] != -1:
            node = self.parent[node]
        return node

    def union(self, i, j):
        i = self.find(i)
        j = self.find(j)

        if i != j:
            if self.size[i] < self.size[j]:
                i, j = j, i
            self.size[i] += self.size[j]
            self.parent[j] = i


def solve():
    # adj stores adjacency list of the tree, store stores updates for each node
    adj = [[], []]
    store = [[], []]

    # Process all queries
    for _ in range(int(input())):
        query = list(map(int, input().split()))
        if query[0] == 1:
            # Type 1 query: add a new child to node
            _, node = query
            adj[node].append(len(adj))  # Add new vertex as child
            store.append([])  # Initialize empty store for new vertex
            adj.append([])  # Initialize empty adjacency list for new vertex
        else:
            # Type 2 query: add value x to subtree of node
            _, node, val = query
            store[node].append((len(store), val))  # Store update with index

    total = 0  # Running total of all updates
    res = [0] * len(store)  # Result array to store values of vertices
    tree = FenwickTree(len(store) + 5)  # Fenwick Tree for efficient range queries
    tree_updates = []  # Stack to track updates in tree
    stack = [(1, 1)]  # Stack for DFS traversal: (node, parent)

    while stack:
        node, parent = stack.pop()
        # Handle parent updates before processing current node
        while tree_updates and tree_updates[-1][0] != parent:
            _, i, val = tree_updates.pop()
            tree.update(i, -val)  # Remove from tree
            total -= val  # Adjust total
        # Apply all updates for current node
        for i, val in store[node]:
            tree_updates.append((node, i, val))
            tree.update(i, val)  # Update tree
            total += val  # Adjust total
        tree_updates.append((node, node, 0))  # Mark current node as visited
        
        # Calculate value for current node
        res[node] = total - tree.query(node)
        # Add children to stack for processing
        for child in adj[node]:
            stack.append((child, node))

    # Final cleanup of tree updates
    for _, i, val in tree_updates:
        tree.update(i, -val)

    print(*res[1:])  # Output values from vertex 1 onwards


t = 1
t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/