# Problem: CF 2050 G - Tree Destruction
# https://codeforces.com/contest/2050/problem/G

"""
G. Tree Destruction

Purpose:
This code solves the problem of finding the maximum number of connected components 
that can be formed after removing a path between two vertices in a tree.

Algorithm:
- The solution uses a depth-first search (DFS) approach to traverse the tree.
- For each node, it computes:
  - The maximum sum of two longest paths from that node to its children (used for computing max_sum).
  - The maximum single path from that node to any child (used in max_single array).
- After computing these values, it determines:
  - The maximum degree in the tree.
  - The maximum number of connected components possible when removing the path from two nodes, using:
    - max_sum: represents the best case where we remove a path which cuts through the tree at the root,
      maximizing the number of disconnected subtrees created.
    - max_deg: represents the scenario when we remove a single leaf and split the tree into more parts.

Time Complexity: O(n) per test case, where n is the number of nodes in the tree. Each node and edge is visited once.
Space Complexity: O(n) for storing adjacency lists and auxiliary arrays.

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: number of nodes n
  - Next n-1 lines: pairs of integers representing edges

Output Format:
- One integer per test case: maximum number of connected components after path removal.
"""

import sys


def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n = int(input[ptr])
        ptr += 1
        adj = [[] for _ in range(n + 1)]
        for __ in range(n - 1):
            u = int(input[ptr])
            v = int(input[ptr + 1])
            adj[u].append(v)
            adj[v].append(u)
            ptr += 2
        degrees = [0] * (n + 1)
        for u in range(1, n + 1):
            degrees[u] = len(adj[u])
        max_deg = max(degrees[1:])
        max_sum = -float("inf")
        max_single = [0] * (n + 1)
        stack = [(1, -1, False)]
        while stack:
            u, parent, visited = stack.pop()
            if not visited:
                stack.append((u, parent, True))
                for v in adj[u]:
                    if v != parent:
                        stack.append((v, u, False))
            else:
                max1 = max2 = 0
                for v in adj[u]:
                    if v == parent:
                        continue
                    current = max_single[v]
                    if current > max1:
                        max2 = max1
                        max1 = current
                    elif current > max2:
                        max2 = current
                # Calculate sum of two longest paths from u to children, plus extra edges
                current_sum = max1 + max2 + (degrees[u] - 2)
                if current_sum > max_sum:
                    max_sum = current_sum
                # Store maximum path going down from node u
                max_single[u] = (degrees[u] - 2) + max1
        answer = max(max_deg, max_sum + 2)
        print(answer)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/