# Problem: CF 1970 G1 - Min-Fund Prison (Easy)
# https://codeforces.com/contest/1970/problem/G1

"""
Algorithm: 
- The problem is to split a tree (since m = n - 1) into two components by removing exactly one edge,
  such that the sum of squares of sizes of the components is minimized.
- The approach uses a tree traversal to compute subtree sizes, then iterates over all possible edges
  to be removed and computes the cost of splitting the tree into two parts.
- Since the tree is a connected acyclic graph, removing one edge partitions it into two subtrees.
- We perform a BFS/DFS traversal to compute the size of each subtree and then evaluate the cost for each potential split.

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing the graph and auxiliary arrays.
"""

import sys
from collections import deque


def main():
    data = sys.stdin.read().split()
    t = int(data[0])  # Number of test cases
    index = 1  # Index pointer to parse input
    out_lines = []  # To store output lines
    for _ in range(t):
        n = int(data[index])  # Number of nodes
        m = int(data[index + 1])  # Number of edges
        c = int(data[index + 2])  # Cost to build a corridor
        index += 3  # Move past n, m, c
        
        # Build adjacency list representation of the graph
        graph = [[] for _ in range(n + 1)]
        for i in range(m):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            graph[u].append(v)
            graph[v].append(u)
        
        # BFS to compute parent and order of nodes
        parent = [-1] * (n + 1)  # Parent of each node in BFS tree
        order = []  # Stores nodes in BFS order (leaf to root)
        q = deque([1])  # Start BFS from node 1
        parent[1] = 0  # Root has no parent
        while q:
            node = q.popleft()
            order.append(node)
            for neighbor in graph[node]:
                if neighbor == parent[node]:
                    continue  # Skip parent to avoid going back
                parent[neighbor] = node
                q.append(neighbor)
        
        # Compute subtree sizes starting from leaves
        size = [1] * (n + 1)  # size[i] = size of subtree rooted at i
        for i in range(len(order) - 1, 0, -1):  # Traverse in reverse BFS order (from leaves to root)
            node = order[i]
            size[parent[node]] += size[node]  # Accumulate sizes upward

        # Try all possible edges to remove (i.e., check all possible splits)
        min_cost = float("inf")
        for i in range(2, n + 1):  # For each node except root
            s = size[i]  # Size of subtree rooted at i
            other = n - s  # Size of the other component
            # Cost = s^2 + other^2
            cost_candidate = s * s + other * other
            if cost_candidate < min_cost:
                min_cost = cost_candidate

        out_lines.append(str(min_cost))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/