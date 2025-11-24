# Problem: CF 1776 M - Parmigiana With Seafood
# https://codeforces.com/contest/1776/problem/M

"""
Problem: Parmigiana di melanzane game on a tree.

Algorithms/Techniques:
- Tree traversal (BFS)
- Game theory (minimax)
- Binary search on answer
- Depth and parent tracking

Time Complexity: O(n * log n)
Space Complexity: O(n)

The problem models a two-player game on a tree where players alternately remove leaves,
with Alessandro trying to maximize the maximum label in the recipe, and Bianca minimizing it.
This is solved using binary search over possible answers combined with a game simulation
to check if a given maximum label can be achieved.
"""

import sys
from collections import deque

input = sys.stdin.buffer.readline
n = int(input())
g = [[] for _ in range(n + 1)]
for _ in range(1, n):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

# BFS to find depths and parents
q = deque()
d = [-1] * (n + 1)
f = [0] * (n + 1)
q.append(n)
d[n] = 0
while len(q):
    u = q.popleft()
    for v in g[u]:
        if d[v] == -1:
            q.append(v)
            f[v] = u
            d[v] = d[u] + 1

# If n is even, the first player (Alessandro) has a winning strategy to take any leaf,
# so he picks n and the result is n itself.
if n % 2 == 0:
    print(n)
else:
    # Binary search on the answer
    l, r = 1, n
    while l < r:
        m = (l + r + 1) // 2
        ok = True
        
        # Check if all nodes from m to n are valid for this threshold
        for i in range(m, n + 1):
            # If node is a leaf or has odd depth, it's not allowed to be taken
            if len(g[i]) == 1 or d[i] % 2:
                ok = False

        # Marking the path from m to root n
        x = [0] * (n + 1)
        x[n] = 1
        for i in range(m, n + 1):
            j = i
            while x[j] == 0:
                x[j] = 1
                j = f[j]

        # Traverse the tree to simulate gameplay
        for i in range(m, n + 1):
            c = 2 if i == n else 1
            for v in g[i]:
                if f[v] == i:
                    c -= x[v]
            for v in g[i]:
                if f[v] == i and c > 0:
                    x[v] = 1
                    c -= 1

        # Verify game simulation is valid for the given threshold
        for i in range(1, n + 1):
            if x[i] and d[i] % 2 == 0:
                y = 0
                for j in g[i]:
                    y += x[j]
                if y > 2:
                    ok = False

        if ok:
            r = m - 1
        else:
            l = m
    print(l)


# https://github.com/VaHiX/codeForces/