# Problem: CF 2037 D - Sharky Surfing
# https://codeforces.com/contest/2037/problem/D

"""
D. Sharky Surfing

Purpose:
This code solves a greedy problem where Mualani needs to surf from position 1 to position L,
avoiding hurdles and collecting the minimum number of power-ups to increase her jump power.

Algorithms/Techniques:
- Greedy approach with a max heap (priority queue) to always select the most beneficial power-up.
- Preprocessing using binary search (bisect_left) to group power-ups by their positions relative to hurdles.
- Efficient simulation of the path traversal using cumulative jump power and greedy selection.

Time Complexity:
O((n + m) * log(m)) per test case, where n is number of hurdles and m is number of power-ups.
This accounts for sorting and heap operations across all positions.

Space Complexity:
O(n + m), to store hurdle information and power-ups grouped by position.
"""

import heapq
import sys
from bisect import bisect_left

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    n, m, l = map(int, input().split())
    ws = []  # Lengths of each hurdle interval
    seps = []  # Start positions of hurdles (used for binary search)
    for _ in range(n):
        a, b = map(int, input().split())
        ws.append(b - a + 1)  # Size of the hurdle interval
        seps.append(a)
    
    # Group power-ups by their positions using separators (hurdle starts)
    locs = [[] for _ in range(n + 1)]
    for _ in range(m):
        x, v = map(int, input().split())
        locs[bisect_left(seps, x)].append(v)  # Place power-up at appropriate hurdle index
    
    p = 1         # Current jump power (starts at 1)
    u = 0         # Number of power-ups collected
    q = []        # Max heap to store available power-ups (negated for max-heap behavior)

    for i in range(n):
        # Add all power-ups located at the current hurdle position to the heap
        for v in locs[i]:
            heapq.heappush(q, -v)
        
        # Greedily consume power-ups until we can pass this hurdle
        while len(q) and p <= ws[i]:  # While still unable to clear hurdle and power-ups exist
            u += 1                    # Collect one power-up
            p -= heapq.heappop(q)     # Add its value to current jump power (negative value -> subtract)
        
        # If we're still not able to pass the hurdle, it's impossible
        if p <= ws[i]:
            print(-1)
            break
    else:
        print(u)  # Successfully passed all hurdles


# https://github.com/VaHiX/codeForces/