# Problem: CF 1693 B - Fake Plastic Trees
# https://codeforces.com/contest/1693/problem/B

"""
Algorithm: Tree Processing with Greedy Approach
Techniques: 
- Post-order traversal of tree
- Greedy assignment of values to minimize operations
- Difference array concept on tree

Time Complexity: O(n) per test case, where n is the number of nodes
Space Complexity: O(n) for storing tree structure and auxiliary arrays

This solution processes the tree in reverse topological order (post-order),
assigning values greedily to minimize the number of operations needed.
It uses a lazy propagation-like technique where we track the "excess" 
values that need to be pushed up the tree, and count how many times 
we must "activate" a node to satisfy its constraints.
"""

import sys

input = lambda: sys.stdin.readline()
for _ in range(int(input())):
    n = int(input())
    p = [0, 0] + list(map(int, input().split()))  # Parent array (1-indexed)
    l, r, now, res = (
        [0 for i in range(n + 1)],  # Lower bounds
        [0 for i in range(n + 1)],  # Upper bounds
        [0 for i in range(n + 1)],  # Current excess values
        0,  # Result counter (number of operations)
    )
    for i in range(n):
        l[i + 1], r[i + 1] = map(int, input().split())  # Read l[i], r[i]
    
    # Process nodes in reverse order (post-order traversal)
    for i in range(n, 0, -1):
        # If current excess is less than the required lower bound,
        # we must perform an operation to raise it to the upper bound
        if now[i] < l[i]:
            now[i] = r[i]  # Set to upper bound to satisfy constraint
            res += 1  # Increment operation counter
        
        # Propagate excess to parent (lazy propagation)
        now[p[i]] += min(now[i], r[i])  # Add the minimum of current excess and upper bound
    
    print(res)


# https://github.com/VaHiX/CodeForces/