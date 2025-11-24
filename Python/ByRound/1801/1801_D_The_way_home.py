# Problem: CF 1801 D - The way home
# https://codeforces.com/contest/1801/problem/D

"""
Algorithm: 
- This is a shortest path problem with a twist: the cost of traveling depends on how much money the magician has, 
  and he can earn money by organizing performances.
- We use a modified Dijkstra's algorithm with a priority queue (min-heap) to find the minimum number of performances.
- For each city, we track:
    - The number of performances so far
    - The money available
    - The current node
    - The maximum earning rate (w[i]) encountered on the path to this node
- When we need to take a flight, if we don't have enough money, we calculate how many performances are needed to gather enough money.
- We only push states to the heap if it's better than what we already have.

Time Complexity: O((V + E) * log V * W), where V is number of cities (n), E is number of flights (m), 
    and W is the maximum earning rate (w[i]). In worst case, each node can be pushed to the heap multiple times.

Space Complexity: O(V + E), to store adjacency list and visited/mx_prize arrays.
"""

import math
import sys
from heapq import heappop, heappush


def IL():
    return list(map(int, sys.stdin.readline().strip().split()))


def S():
    return sys.stdin.readline().strip()


def solve():
    n, m, p = IL()
    w = [0] + IL()  # w[0] unused, w[i] is profit from city i

    adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b, wi = IL()
        adj[a].append((b, wi))

    # (performances, -coins, node, max_earning_rate)
    heap = [(0, -p, 1, w[1])]
    vis = [0] * (n + 1)          # visited marker for nodes
    mx_prize = [0] * (n + 1)     # max earning rate seen so far on path to each node
    
    while heap:
        cur_perform, cur_coin, node, mx = heappop(heap)
        cur_coin *= -1  # negate back to positive
        
        # Skip if already processed with better or equal earnings
        if vis[node] == 1 and mx_prize[node] >= mx:
            continue

        vis[node] = 1
        mx_prize[node] = mx
        
        if node == n:
            print(cur_perform)
            return

        for nei, weight in adj[node]:
            if weight > cur_coin:
                # Not enough money to take this flight
                diff = weight - cur_coin
                # Calculate how many performances needed
                x = math.ceil(diff / mx)
                new_coin = cur_coin + (x * mx)
                nxt_perform = cur_perform + x
                nxt_coin = new_coin - weight
            else:
                # Enough money to take the flight
                nxt_perform = cur_perform
                nxt_coin = cur_coin - weight
                
            # Push only if we haven't been to nei with better or equal earnings
            if not (vis[nei] == 1 and mx_prize[nei] >= max(mx, w[nei])):
                heappush(heap, (nxt_perform, -nxt_coin, nei, max(w[nei], mx)))
                
    print(-1)  # Impossible to reach


tt = IL()[0]
for _ in range(tt):
    solve()


# https://github.com/VaHiX/CodeForces/