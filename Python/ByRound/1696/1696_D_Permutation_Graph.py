# Problem: CF 1696 D - Permutation Graph
# https://codeforces.com/contest/1696/problem/D

"""
Code Purpose:
This solution finds the shortest path from vertex 1 to vertex n in a graph constructed from a permutation.
The graph has edges based on min/max conditions between indices. The algorithm uses monotonic stacks
to efficiently determine which nodes are directly connected, then performs a greedy traversal to find
the shortest path.

Algorithms/Techniques:
- Monotonic stacks to precompute next smaller/larger elements
- Greedy path traversal to find shortest path

Time Complexity: O(n) amortized for each test case
Space Complexity: O(n) for storing the graph and stacks
"""

for case in range(int(input())):
    _ = int(input())
    a = [int(i) for i in input().split()]
    g = [float("inf") for i in a]  # g[i] stores index of next greater element
    l = [float("inf") for i in a]  # l[i] stores index of next smaller element
    gt = []  # Stack for greater elements (monotonic decreasing)
    lt = []  # Stack for smaller elements (monotonic increasing)
    
    # Traverse from right to left to compute next greater and smaller elements
    for i, n in reversed(list(enumerate(a))):
        # Maintain decreasing stack for next greater element
        while gt and n > gt[-1][0]:
            gt.pop()
        if gt:
            g[i] = gt[-1][1]
        gt.append((n, i))
        
        # Maintain increasing stack for next smaller element
        while lt and n < lt[-1][0]:
            lt.pop()
        if lt:
            l[i] = lt[-1][1]
        lt.append((n, i))
    
    p = 0  # Current position (vertex index)
    cnt = 0  # Step count for shortest path
    
    # Greedy traversal from vertex 1 to vertex n
    while p != len(a) - 1:
        cnt += 1
        # Decide which direction to go based on the smaller index
        if g[p] > l[p]:
            t = g[p]
            # Move while the current node's smaller index is less than target
            while l[p] < t:
                p = l[p]
        else:
            t = l[p]
            # Move while the current node's greater index is less than target
            while g[p] < t:
                p = g[p]
    
    print(cnt)


# https://github.com/VaHiX/CodeForces/