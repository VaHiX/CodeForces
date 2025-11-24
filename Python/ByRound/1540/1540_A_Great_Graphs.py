# Problem: CF 1540 A - Great Graphs
# https://codeforces.com/contest/1540/problem/A

"""
A. Great Graphs
Algorithms/Techniques: Sorting, Greedy, Math

Time Complexity: O(n log n) due to sorting step
Space Complexity: O(1) excluding input storage

The problem asks for the minimum cost of a directed graph such that 
the shortest path from node 1 to all other nodes matches the given array d.
We model this as a construction problem where we can add edges with negative weights
to minimize total edge cost.

The algorithm works by:
1. Sorting the distances in ascending order.
2. For each adjacent pair in sorted order, calculate how much we need to "pay"
   for the difference in distances by adding edges.
3. Accumulate these costs to compute minimal total cost.
"""

import sys

input = sys.stdin.readline
t = int(input())
for tests in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()
    res = 0
    sumi = arr[-1]
    for i in range(n - 1):
        # For each adjacent pair of distances, calculate contribution to total cost
        res += (arr[i + 1] - arr[i]) * (i + 1) * (n - i - 1)
    print(sumi - res)


# https://github.com/VaHiX/codeForces/