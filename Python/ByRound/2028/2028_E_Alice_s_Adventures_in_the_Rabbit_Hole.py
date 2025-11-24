# Problem: CF 2028 E - Alice's Adventures in the Rabbit Hole
# https://codeforces.com/contest/2028/problem/E

"""
E. Alice's Adventures in the Rabbit Hole

Purpose:
This code computes the probability that Alice escapes from each vertex of a tree,
given a game where at each step, a fair coin is flipped. If heads, Alice moves to a 
random adjacent node; if tails, the Queen of Hearts pulls Alice to a node optimally chosen 
to minimize her escape chance. The problem is solved using dynamic programming on trees,
with BFS to compute distances and then DP traversal to calculate escape probabilities.

Algorithms/Techniques:
- Tree BFS traversal to build parent-child relationships.
- Dynamic Programming with memoization to compute probability of escaping from each vertex.
- Modular arithmetic for finite field operations (mod 998244353).
- Inverse modulo using pow(a, -1, mod) for modular division.

Time Complexity:
O(n) per test case, where n is the number of vertices. Each node is visited twice:
once in BFS to build data structures and once in DP traversal.

Space Complexity:
O(n) for storing adjacency lists, parent array, depth array, and DP values.
"""

import sys

input = sys.stdin.readline
mod = 998244353

for i in range(int(input())):
    n = int(input())
    g = [[] for j in range(n)]
    for j in range(n - 1):
        u, v = map(int, input().split())
        g[u - 1].append(v - 1)
        g[v - 1].append(u - 1)
    
    # p[i] stores parent of node i
    p = [0] * n
    
    # vis[i] tracks visited nodes during BFS
    vis = [(0 if j else 1) for j in range(n)]
    
    # s is stack for BFS traversal
    s, t = [0], [0]
    
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                p[child] = parent
                t.append(child)
                s.append(child)
    
    # d[i] stores the distance to root (vertex 0) from each node
    d = [0] * n
    
    for j in range(n - 1, 0, -1):
        if d[p[t[j]]] == 0 or d[p[t[j]]] > d[t[j]] + 1:
            d[p[t[j]]] = d[t[j]] + 1

    # dp[i] stores the escape probability from node i
    dp = [(0 if j else 1) for j in range(n)]
    
    # vis[i] used in second BFS to mark visited nodes during DP
    vis = [(0 if j else 1) for j in range(n)]
    
    s = [0]
    
    while s:
        parent = s.pop()
        for child in g[parent]:
            if not (vis[child]):
                vis[child] = 1
                # Compute probability using modular arithmetic:
                # dp[child] = dp[parent] * d[child] * inverse(d[child]+1)
                dp[child] = (dp[parent] * d[child] * pow(d[child] + 1, -1, mod)) % mod
                s.append(child)

    print(*dp)


# https://github.com/VaHiX/codeForces/