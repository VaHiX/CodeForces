# Problem: CF 2117 F - Wildflower
# https://codeforces.com/contest/2117/problem/F

"""
F. Wildflower

Purpose:
This code solves a dynamic programming problem on trees where we need to count the number of ways to assign values 1 or 2 to each node such that all subtree sums are distinct.

Algorithms/Techniques:
- Tree traversal with DFS
- Dynamic Programming on Trees (based on leaf structure)
- Modular exponentiation

Time Complexity: O(N) per test case, where N is the number of nodes.
Space Complexity: O(N) for storing tree and auxiliary arrays.

Approach:
1. Identify all leaves in the tree.
2. If there are more than 2 leaves, return 0 (impossible to have unique subtree sums).
3. If there's exactly one leaf, result is 2^N mod (10^9 + 7).
4. Otherwise, find paths from two leaves towards root and compute DP states.

"""

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    G = [[] for i in range(N)]
    for i in range(N - 1):
        a, b = map(int, input().split())
        G[a - 1].append(b - 1)
        G[b - 1].append(a - 1)
    leaf = []
    for i in range(1, N):  # Start from 1 since root is 0
        if len(G[i]) == 1:
            leaf.append(i)
    if len(leaf) > 2:
        print(0)
        continue
    mod = 10**9 + 7
    if len(leaf) == 1:
        result = pow(2, N, mod)
        print(result)
        continue
    a, b = leaf[:]
    n, m = 0, 0
    used = [False] * N
    used[a] = True
    used[b] = True
    while True:
        for c in G[a]:
            if used[c] == False:
                used[c] = True
                a = c
        n += 1
        if len(G[a]) > 2:  # If current node has more than 2 neighbors, stop path traversal
            break
        if a == 0:  # Reached the root
            break
    used = [False] * N
    used[b] = True
    while True:
        for c in G[b]:
            if used[c] == False:
                used[c] = True
                b = c
        m += 1
        if len(G[b]) > 2:  # If current node has more than 2 neighbors, stop path traversal
            break
        if b == 0:  # Reached the root
            break
    if n == m:
        result = pow(2, N - 2 * m + 1, mod)
    else:
        result = pow(2, N - 2 * min(n, m) - 1, mod) + pow(2, N - 2 * min(n, m), mod)
        result %= mod
    print(result)


# https://github.com/VaHiX/codeForces/