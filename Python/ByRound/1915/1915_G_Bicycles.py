# Problem: CF 1915 G - Bicycles
# https://codeforces.com/contest/1915/problem/G

"""
Algorithm: Dijkstra's with modified state
Time Complexity: O((V + E) * log V) where V is number of cities and E is number of roads
Space Complexity: O(V + E) for graph storage and priority queue

The problem is a variant of shortest path where each edge weight is multiplied by the slowness 
factor of the bike currently being used. The key insight is that we keep track of the minimum 
slowness factor so far in the path, and use that to compute edge weights.

We use a priority queue (min-heap) to perform Dijkstra's algorithm, storing:
- Time taken to reach a node
- Current slowness factor (minimum so far in path)
- Current node

At each step, we update neighbors using the current slowness factor for edge weight calculation.
"""

from heapq import heappop, heappush
from sys import stdin


def calc_least_time(graph, s):
    n = len(graph)
    # Initialize heap with (time, current_slowness_factor, node)
    heap = [(0, s[0], 0)]
    # Track minimum slowness factor seen for each city
    curr_coefs = [s[0] + 1] * n
    while heap:
        t, coef, v = heappop(heap)
        # If we reached destination, return time
        if v == n - 1:
            return t
        # Skip if we already found a better path to this node
        if coef >= curr_coefs[v]:
            continue
        # Update minimum slowness factor for current node
        coef = min(coef, s[v])
        curr_coefs[v] = coef
        # Explore neighbors
        for u, w in graph[v]:
            # If neighbor hasn't been visited with better slowness factor
            if curr_coefs[u] > coef:
                # Push to heap with updated time and current slowness factor
                heappush(heap, (t + w * coef, coef, u))
    assert False, ("not reachable?", graph)


n_tests = int(input())
for test_id in range(n_tests):
    n, m = map(int, stdin.readline().split())
    graph = [[] for i in range(n)]
    for i in range(m):
        u, v, w = map(int, stdin.readline().split())
        # Build adjacency list for undirected graph
        graph[u - 1].append((v - 1, w))
        graph[v - 1].append((u - 1, w))
    s = list(map(int, stdin.readline().split()))
    assert len(s) == n
    print(calc_least_time(graph, s))


# https://github.com/VaHiX/CodeForces/