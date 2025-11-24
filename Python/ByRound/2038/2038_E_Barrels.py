# Problem: CF 2038 E - Barrels
# https://codeforces.com/contest/2038/problem/E

import sys
from collections import deque

"""
Algorithm: 
- This solution uses a deque-based approach to simulate the water distribution in barrels.
- It processes barrels from right to left, maintaining a deque of segments.
- Each segment represents a range of barrels with a common water level.
- The algorithm simulates adding clay and calculates equilibrium water levels.
- Time Complexity: O(n)
- Space Complexity: O(n)

The key idea is to process from right to left and simulate the water flow dynamics.
We maintain segments in the deque where each segment has a fixed water level and a range [x, y].
The pipe heights determine whether water can flow between barrels.
"""

n = int(sys.stdin.readline())
v = list(map(int, sys.stdin.readline().split()))
h = list(map(int, sys.stdin.readline().split()))
dq = deque()
eps = 1e-9
for i in range(n - 1, 0, -1):
    if not dq:
        dq.append((float(v[i]), (i, i)))
    tmp = h[i - 1]
    while tmp > eps:
        x, y = dq[-1][1]
        l = y - x + 1
        # If we can merge segments or adjust water level
        if len(dq) > 1 and (x == 0 or (h[x - 1] >= h[y])):
            # If the amount needed to fill the gap is less than the remaining water
            if tmp >= (h[y] - dq[-1][0]) * l:
                tmp -= (h[y] - dq[-1][0]) * l
                dq.pop()
                last_val, (last_x, last_y) = dq[-1]
                dq[-1] = (last_val, (x, last_y))
            else:
                # Partially fill the gap
                new_val = dq[-1][0] + tmp / l
                dq[-1] = (new_val, (x, y))
                tmp = 0
        else:
            # Consider the pipe at x-1
            if x > 0 and tmp >= (h[x - 1] - dq[-1][0]) * l:
                tmp -= (h[x - 1] - dq[-1][0]) * l
                dq[-1] = (h[x - 1], (x, y))
                dq.append((float(v[x - 1]), (x - 1, x - 1)))
            else:
                new_val = dq[-1][0] + tmp / l
                dq[-1] = (new_val, (x, y))
                tmp = 0
    first_val, (first_x, first_y) = dq[0]
    first_y -= 1
    if first_y < first_x:
        dq.popleft()
    else:
        dq[0] = (first_val, (first_x, first_y))
print("{0:.12f}".format(dq[-1][0]))


# https://github.com/VaHiX/CodeForces/