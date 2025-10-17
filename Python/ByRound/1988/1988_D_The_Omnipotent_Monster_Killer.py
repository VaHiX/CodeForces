# Problem: CF 1988 D - The Omnipotent Monster Killer
# https://codeforces.com/contest/1988/problem/D

"""
D. The Omnipotent Monster Killer

Purpose:
This code solves a tree-based optimization problem where the goal is to minimize the cumulative damage
received over many rounds of battle against monsters on a tree. In each round, all alive monsters attack,
and then we can choose a subset of non-adjacent monsters to kill. The solution uses dynamic programming on
a tree with subtree merging techniques.

Algorithms/Techniques:
- Tree Dynamic Programming (DP)
- Binary lifting / Heavy-Light Decomposition simulation using DFS traversal
- Pruning and optimization of minimum cost selection per node in subtree

Time Complexity: O(n * log n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing graph and DP arrays.

Input Format:
- Number of test cases T
- For each test case:
  - n (number of nodes)
  - Array a of n integers representing attack values
  - n-1 edges defining the tree structure

Output:
- Minimum possible total damage over all rounds, modulo 10^9+7 if needed (not explicitly stated here).
"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
T = sint()
big = float("inf")
for _ in range(T):
    n = sint()
    m = n.bit_length() + 1
    a = [0] + aint()  # 1-indexed array of monster attacks
    g = [[] for _ in range(n + 1)]  # adjacency list for the tree
    for _ in range(n - 1):
        u, v = map(int, input().split())
        g[u].append(v)
        g[v].append(u)
    
    # dp[i][j] stores the cost to select j monsters from subtree rooted at i
    dp = [[a[i] * (b + 1) for b in range(len(g[i]) + 1)] for i in range(n + 1)]
    x = [0] * (n + 1)  # extra costs propagated up the tree
    
    Q = [(0, 1)]  # Stack-based DFS: (parent, child)
    
    while Q:
        f, c = Q.pop()
        if c > 0:
            # Push back with inverted flag for post-processing
            Q.append((f, ~c))
            # Traverse neighbors excluding parent
            for i in g[c]:
                if i == f:
                    continue
                Q.append((c, i))
        else:
            # Post-order processing of node c (i.e., after children processed)
            c = ~c
            mi = -1  # index of minimal value in dp[c]
            mv = big  # minimum value in dp[c]
            sv = big  # second minimum value in dp[c]
            
            for i, val in enumerate(dp[c]):
                if val <= mv:
                    sv = mv
                    mi = i
                    mv = val
                elif val < sv:
                    sv = val

            # Merge contribution from this node to parent
            x[f] += mv + x[c]
            
            # Adjust dp of parent if not root
            if mi < len(dp[f]):
                dp[f][mi] += sv - mv  # Propagate optimal choice to avoid conflict

    ans = min(dp[1]) + x[1]
    print(ans)


# https://github.com/VaHiX/codeForces/