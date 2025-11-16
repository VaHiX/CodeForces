# Problem: CF 1833 E - Round Dance
# https://codeforces.com/contest/1833/problem/E

"""
Problem: Round Dance
Algorithm: Graph traversal to find cycles in a directed graph where each node has exactly one outgoing edge.
Each person remembers one neighbor, so we can model this as a directed graph where edge from i to a[i].
We need to find minimum and maximum number of cycles (round dances).

Approach:
1. For minimum cycles: We count the number of "non-bridge" cycles.
2. For maximum cycles: We compute the number of components in the graph.

Time Complexity: O(n) - Each node is visited at most twice.
Space Complexity: O(n) - For visited array and other auxiliary arrays.
"""

import sys

input = sys.stdin.buffer.readline

infinity = 10**10

for _ in range(int(input())):
    n = int(input())
    a = [int(x) - 1 for x in input().split()]

    mentioned = [False] * n
    for x in a:
        mentioned[x] = True

    minimum = 0
    maximum = 0
    visited = [0] * n
    once = False
    for i in range(n):
        if mentioned[i]:
            continue
        j = i
        while visited[j] == 0:
            visited[j] = 1
            j = a[j]

        if visited[j] == 1:
            maximum += 1
            once = True

        j = i
        while visited[j] == 1:
            visited[j] = 2
            j = a[j]

    for i in range(n):
        if visited[i] == 2:
            continue

        j = i
        while visited[j] == 0:
            visited[j] = 2
            j = a[j]

        if a[a[j]] != j:
            minimum += 1
        else:
            once = True

        maximum += 1

    print(minimum + once, maximum)


# https://github.com/VaHiX/CodeForces/