# Problem: CF 1693 C - Keshi in Search of AmShZ
# https://codeforces.com/contest/1693/problem/C

"""
Purpose: 
Find the minimum number of days required for Keshi to reach city n from city 1,
given that AmShZ can block roads or instruct Keshi to move each day.
This problem is modeled as a shortest path problem on a directed graph where:
- Each node represents a city.
- Each edge represents a directed road.
- We use a modified Dijkstra's algorithm with a priority queue to find the minimum steps.
- For each node, we track the minimum number of operations needed to reach it.
- The weight of moving from a node is based on the in-degree of the neighbor node.
- This is essentially a reverse topological traversal with weighted edges, using Dijkstra's.

Time Complexity: O((V + E) * log V), where V is number of cities and E is number of roads.
Space Complexity: O(V + E), for storing the graph and auxiliary arrays.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

n, m = map(int, input().split())
edge = [[] for i in range(n)]
ord = [0] * n
for _ in range(m):
    a, b = map(lambda x: int(x) - 1, input().split())
    edge[b].append(a)
    ord[a] += 1

inf = 1 << 30
dist = [inf] * n
from heapq import heappop, heappush

# Start from city n (destination) and compute distances backward
hq = [(0, n - 1)]
dist[n - 1] = 0
seen = [False] * n
while hq:
    w, v = heappop(hq)
    if dist[v] < w:
        continue
    seen[v] = True
    # Traverse all predecessors of v
    for to in edge[v]:
        # Update the distance if going through this edge is better
        if dist[v] + ord[to] < dist[to]:
            dist[to] = dist[v] + ord[to]
            heappush(hq, (dist[to], to))
        # Decrease the out-degree of the predecessor (simulate blocking)
        ord[to] -= 1

# The answer is the minimum distance to reach city 1 (index 0)
print(dist[0])


# https://github.com/VaHiX/CodeForces/