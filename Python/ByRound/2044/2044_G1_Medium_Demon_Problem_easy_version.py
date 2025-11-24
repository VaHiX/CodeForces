# Problem: CF 2044 G1 - Medium Demon Problem (easy version)
# https://codeforces.com/contest/2044/problem/G1

"""
Problem: Spider Plushie Exchange

This problem models a directed graph where each node (spider) gives one plushie to another node (recipient).
The process stabilizes when the number of plushies each spider has remains constant over two consecutive years.

Algorithm:
- Build a dependency graph represented by in-degrees.
- Simulate the plushie exchange year by year using BFS-like approach on nodes with in-degree 0.
- Each round represents one year of exchange.
- Time Complexity: O(n)
- Space Complexity: O(n)

Techniques:
- Topological sorting concept using in-degrees
- Simulation of process steps
"""

import sys

input = sys.stdin.readline
t = int(input())
for tests in range(t):
    n = int(input())
    A = list(map(int, input().split()))
    # Convert to 0-based indexing
    for i in range(n):
        A[i] -= 1
    # DEG[i] stores the in-degree of node i
    DEG = [0] * n
    for a in A:
        DEG[a] += 1
    # Q holds nodes (spiders) with in-degree 0
    Q = []
    for i in range(n):
        if DEG[i] == 0:
            Q.append(i)
    ANS = 0
    # Simulate the process year by year until all nodes are processed
    while Q:
        ANS += 1
        NQ = []
        # Process all current nodes (spiders with in-degree 0)
        for q in Q:
            # Reduce in-degree of the recipient node
            DEG[A[q]] -= 1
            # If new in-degree becomes 0, add to next queue
            if DEG[A[q]] == 0:
                NQ.append(A[q])
        Q = NQ
    # Add 2 because year 1 is never stable, and we're counting from the first stable year
    print(ANS + 2)


# https://github.com/VaHiX/codeForces/