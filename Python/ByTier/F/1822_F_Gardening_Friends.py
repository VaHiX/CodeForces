# Problem: CF 1822 F - Gardening Friends
# https://codeforces.com/contest/1822/problem/F

"""
Code Purpose:
This code solves the problem of finding the maximum profit from a tree by choosing the optimal root. 
The profit is defined as the cost of the tree (maximum distance from root to any node) minus the cost of shifting the root.
The approach uses two BFS traversals to find the diameter of the tree and then evaluates all possible root positions to maximize profit.

Algorithms/Techniques:
- BFS (Breadth-First Search) to find the farthest node from a given node (first BFS)
- BFS to find the distance from the farthest node to all other nodes (second BFS)
- Tree diameter calculation using two BFS
- Evaluation of all possible root positions using the precomputed distances

Time Complexity: O(n) where n is the number of vertices in the tree. Each BFS runs in O(n) time, and the final loop also takes O(n).
Space Complexity: O(n) for storing adjacency list, distance arrays, and the queue.

"""

import sys
from collections import deque

input = sys.stdin.readline


def fgh():
    return [int(xx) for xx in input().split()]


def fg():
    return int(input())


for PeTr_ZzZzAtOcHkIn in range(fg()):  # Process each test case
    n, k, ac = fgh()  # Read n (vertices), k (edge length), c (cost per operation)
    a = [[] for i in range(n)]  # Build adjacency list for the tree
    for i in range(n - 1):
        u, v = fgh()
        a[u - 1].append(v - 1)  # Convert to 0-based indexing
        a[v - 1].append(u - 1)
    
    q = deque()  # Queue for BFS
    q.append(0)  # Start BFS from node 0
    do = [1111001111] * n  # Distance from root to each node (initialized with large value)
    do[0] = 0  # Distance to root is 0
    
    # First BFS to find farthest node from the starting node (0)
    while len(q):
        c = q.popleft()  # Current node
        for u in a[c]:  # For each neighbor
            if do[u] > 10000000:  # If not visited
                do[u] = do[c] + 1  # Update distance
                q.append(u)  # Add to queue
    
    f = do.index(max(do))  # Find the index of the farthest node from root
    
    q = deque()
    q.append(f)  # Start second BFS from the farthest node
    d = [1111001111] * n  # Distance from the farthest node to each node
    d[f] = 0  # Distance to the farthest node is 0
    
    # Second BFS to calculate distance from the farthest node to all others
    while len(q):
        c = q.popleft()
        for u in a[c]:
            if d[u] > 10000000:  # If not visited
                d[u] = d[c] + 1
                q.append(u)
    
    ans = -111110  # Initialize maximum profit with a very small value
    # Evaluate all possible root positions to find maximum profit
    for i in range(n):
        # Profit = cost - operations_cost = max_distance * k - distance_from_root * c
        ans = max(ans, d[i] * k - do[i] * ac)
    
    print(ans)  # Output the maximum profit


# https://github.com/VaHiX/CodeForces/