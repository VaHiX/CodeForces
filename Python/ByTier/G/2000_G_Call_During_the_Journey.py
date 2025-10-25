# Problem: CF 2000 G - Call During the Journey
# https://codeforces.com/contest/2000/problem/G

"""
G. Call During the Journey

Purpose:
This problem involves finding the latest time one can leave home (intersection 1) to still make it to an event at intersection n on time, 
while also making a phone call from time t1 to t2.

Algorithm:
- A modified Dijkstra's algorithm is used with a priority queue.
- The key insight is that during the phone call period [t1, t2], buses cannot be taken but walking is allowed.
- For each edge (street), we store both bus and walking times.
- Time spent on edges changes based on whether the current time allows boarding the bus or not.

Key Concepts:
- Time-dependent graph traversal: different edge weights depending on current time.
- Priority queue with negative time for max-heap simulation.
- Special handling of phone call constraints.

Time Complexity:
O((n + m) * log n), where n is number of intersections, m is number of streets.
Space Complexity:
O(n + m): for adjacency list and auxiliary arrays.
"""

import sys

input = sys.stdin.readline
from heapq import heappop, heappush

for _ in range(int(input())):
    n, m = map(int, input().split())
    t0, t1, t2 = map(int, input().split())
    d = [[] for _ in range(n + 1)]
    q = []
    for i in range(m):
        a, b, l1, l2 = map(int, input().split())
        d[a].append((b, i))
        d[b].append((a, i))
        q.append((l1, l2))
    h = [(~t0, n)]  # Using negative to simulate max-heap
    x = [-1] * (n + 1)  # x[i] stores the latest time we can arrive at node i
    y = [1] * m  # y[j] tracks if edge j has been processed
    while h:
        a, b = heappop(h)
        a = ~a  # Restore actual time value
        if a >= x[b]:
            x[b] = a
            for i, j in d[b]:
                if y[j]:  # Process edge j only once
                    y[j] = 0
                    a1 = a
                    l1, l2 = q[j]
                    # If it's during the phone call period or just before it ends,
                    # switch to walking and assume no bus can be taken
                    if t1 < a <= t2 or (t2 <= a and a - l1 < t2):
                        a1 = t1  # Set time to start of the phone call, effectively skipping bus
                    # Compute how long since arriving at node i (a2)
                    a2 = max(a - l2, a1 - l1)
                    if a2 > -1 and a2 > x[i]:
                        x[i] = a2
                        heappush(h, (~a2, i))  # Push with negative to maintain max-heap property
    print(x[1])


# https://github.com/VaHiX/codeForces/