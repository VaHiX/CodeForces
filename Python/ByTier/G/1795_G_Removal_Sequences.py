# Problem: CF 1795 G - Removal Sequences
# https://codeforces.com/contest/1795/problem/G

"""
Algorithm: Removal Sequences
Purpose: To count the number of "nice" pairs (x, y) such that there exist two valid removal sequences where x is removed before y in one and y before x in another.

Approach:
1. Build the graph and adjust degree requirements as (actual_degree - required_degree).
2. Use a topological-like process to compute removal order.
3. For each vertex, track which vertices it can "see" in the final ordering.
4. Use bit manipulation with blocks to efficiently compute the result.

Time Complexity: O(n * B + m) where B = 63, so effectively O(n + m)
Space Complexity: O(n + m) due to adjacency list, degree adjustments, and queues.

The algorithm simulates valid removal sequences, identifies which vertices can precede others,
and uses a bitmasked technique to quickly compute how many pairs are not "nice".
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
out = []
B = 63


def popcount(x):
    # Count number of 1-bits in x using bitwise operations
    x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555)
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333)
    x = (x & 0x0F0F0F0F0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F0F0F0F0F)
    x = (x & 0x00FF00FF00FF00FF) + ((x >> 8) & 0x00FF00FF00FF00FF)
    x = (x & 0x0000FFFF0000FFFF) + ((x >> 16) & 0x0000FFFF0000FFFF)
    x = (x & 0x00000000FFFFFFFF) + ((x >> 32) & 0x00000000FFFFFFFF)
    return x


for _ in range(int(input())):
    n, m = map(int, input().split())
    A = list(map(int, input().split()))
    G = [[] for _ in range(n)]
    for _ in range(m):
        v, u = map(int, input().split())
        G[u - 1].append(v - 1)
        G[v - 1].append(u - 1)

    # Adjust degree requirements: actual_degree - required_degree
    A = [len(G[i]) - a for i, a in enumerate(A)]
    Q = [i for i, a in enumerate(A) if a == 0]  # Initial vertices ready to be removed

    # Simulate removal process to get a valid topological order
    for i in range(n):
        u = Q[i]
        g = []
        for v in G[u]:
            if A[v]:
                g.append(v)
                A[v] -= 1
                if not A[v]:
                    Q.append(v)
        G[u] = g

    pos = [0] * n  # Position of each vertex in the removal order
    for i, u in enumerate(Q):
        pos[u] = i

    X = []
    Y = []
    # Record pairs of removal order indices
    for i, u in enumerate(Q):
        for v in G[u]:
            X.append(i)
            Y.append(pos[v])

    ans = n * (n + 1) // 2  # Total possible pairs (x, y) where x < y
    mask = [0] * n

    # Process blocks of size B = 63 for efficient bit operations
    for l in range(0, n, B):
        r = min(n, l + B)
        # Initialize the mask for current block
        for i in range(l, r):
            mask[i] = 1 << (i - l)

        # Propagate the mask information backward
        for u, v in zip(X, Y):
            mask[v] |= mask[u]

        # Subtract from total pairs the number of pairs where x can come before y (i.e., where mask[y] has 1 at position i)
        for i in range(l, n):
            ans -= popcount(mask[i])
            mask[i] = 0

    out.append(ans)

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/