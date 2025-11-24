# Problem: CF 2014 F - Sheriff's Defense
# https://codeforces.com/contest/2014/problem/F

"""
F. Sheriff's Defense

Problem Description:
The Sheriff of Nottingham needs to protect his camps from Robin Hood's attack. Each camp has some gold,
and strengthening a camp reduces the gold of its neighboring camps by a fixed amount 'c'.
A camp survives if it is strengthened, and all others are destroyed.
The goal is to maximize the total gold in surviving camps.

Approach:
This problem uses dynamic programming on trees with the following idea:
- For each node (camp), decide whether to strengthen it or not.
- If we strengthen a camp:
    - We add its gold to the result
    - We reduce the gold of all neighbors by c
- The decision is made greedily using DP:
    - dp0[node]: max gold if we DON'T strengthen this node
    - dp1[node]: max gold if we DO strengthen this node

Time Complexity: O(n) per test case, since each node is visited once.
Space Complexity: O(n) for storing the tree and DP arrays.

Algorithms/Techniques:
- Tree Dynamic Programming
- Post-order traversal with stack
- Greedy decision making at each node based on children's states
"""

import sys

input = sys.stdin.read
data = input().split()
idx = 0
t = int(data[idx])
idx += 1
for _ in range(t):
    n, c = int(data[idx]), int(data[idx + 1])
    idx += 2
    a = list(map(int, data[idx : idx + n]))
    idx += n
    adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u = int(data[idx])
        v = int(data[idx + 1])
        idx += 2
        adj[u].append(v)
        adj[v].append(u)
    dp0 = [0] * (n + 1)
    dp1 = [0] * (n + 1)
    stack = [(1, 0, False)]
    while stack:
        node, parent, visited = stack.pop()
        if not visited:  # Pre-order processing
            stack.append((node, parent, True))
            for neighbor in reversed(adj[node]):  # Reverse to keep order consistent
                if neighbor != parent:
                    stack.append((neighbor, node, False))
        else:  # Post-order processing
            sum_dp0 = 0  # Sum of max values from children if we don't strengthen this node
            sum_dp1 = 0  # Sum of max values from children if we do strengthen this node
            for child in adj[node]:
                if child != parent:
                    sum_dp0 += max(dp0[child], dp1[child])
                    option = max(dp0[child], dp1[child] - 2 * c)
                    sum_dp1 += option
            dp0[node] = sum_dp0
            dp1[node] = a[node - 1] + sum_dp1  # Add own gold when strengthening
    print(max(dp0[1], dp1[1]))


# https://github.com/VaHiX/codeForces/