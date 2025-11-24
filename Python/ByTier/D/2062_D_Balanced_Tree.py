# Problem: CF 2062 D - Balanced Tree
# https://codeforces.com/contest/2062/problem/D

"""
D. Balanced Tree

This problem involves balancing values in a tree by performing operations that increase values in subtrees.

Algorithm:
- This uses a centroid decomposition approach with BFS-like processing.
- We identify leaves (degree 1 nodes) and process them iteratively.
- For each leaf, we adjust its value based on its neighbor's current value to minimize the final result.
- The key idea is to propagate changes from leaves upwards in the tree.

Time Complexity: O(n) per test case due to processing each node once in BFS order.
Space Complexity: O(n) for storing adjacency information, degrees, and auxiliary arrays.

Input:
- Number of nodes n
- For each node i: l[i] and r[i] - constraints on value
- Edges defining the tree

Output:
- Minimum possible value that all nodes can be made equal to
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
from collections import deque


def solve():
    n = int(input())
    l, r = [None] * n, [None] * n
    for i in range(n):
        l[i], r[i] = map(int, input().split())
    if n == 1:
        return l[0]
    deg = [0] * n      # Degree of each node
    mix = [0] * n      # XOR-based neighbor tracking
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        deg[u] += 1
        deg[v] += 1
        mix[u] ^= v
        mix[v] ^= u
    h = deque(i for i, u in enumerate(deg) if u == 1)  # Queue of leaves (degree 1 nodes)
    ans = 0
    for _ in range(n - 1):
        u = h.popleft()
        v = mix[u]         # Get the neighbor of node u
        # If current leaf's left bound is greater than neighbor's right bound,
        # we must move value from neighbor to this node
        if l[u] > r[v]:
            ans += l[u] - r[v]
            l[v] = r[v]
        elif l[u] > l[v]:
            l[v] = l[u]
        mix[v] ^= u        # Update the XOR tracking for neighbor v
        deg[v] -= 1        # Decrement degree of v and check if it becomes leaf
        if deg[v] == 1:
            h.append(v)
    return ans + l[h[0]]   # Return total adjustments plus final value


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/