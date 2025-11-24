# Problem: CF 1851 E - Nastya and Potions
# https://codeforces.com/contest/1851/problem/E

"""
Algorithm: Topological Sorting + Dynamic Programming
Purpose: Find the minimum cost to obtain each potion type, considering that some potions can be made by mixing others.
Time Complexity: O(n + m) where n is the number of potion types and m is the total number of mixing relationships.
Space Complexity: O(n + m) for storing the graph and costs.

This solution uses topological sorting to process potions in the correct order. For each potion that can be made by mixing others,
we compute the minimal cost as the sum of costs of the ingredients, compared to the cost of buying the potion directly.
"""

import sys

input = sys.stdin.readline


def topo_order(graph):
    n = len(graph)
    in_deg = [0] * n
    for node in range(n):
        for nei in graph[node]:
            in_deg[nei] += 1

    reversed_topo = [node for node in range(n) if in_deg[node] == 0]
    for node in reversed_topo:
        for nei in graph[node]:
            in_deg[nei] -= 1
            if in_deg[nei] == 0:
                reversed_topo.append(nei)
    return reversed_topo[::-1]


for _ in range(int(input())):
    n, k = [int(x) for x in input().split()]
    cost = [int(x) for x in input().split()]
    free_potitions = [int(x) - 1 for x in input().split()]
    for node in free_potitions:
        cost[node] = 0
    graph = [[int(x) - 1 for x in input().split()][1:] for _ in range(n)]

    topo = topo_order(graph)
    for node in topo:
        if not graph[node]:
            continue
        s = 0
        for nei in graph[node]:
            s += cost[nei]
        cost[node] = min(cost[node], s)

    print(*cost)


# https://github.com/VaHiX/CodeForces/