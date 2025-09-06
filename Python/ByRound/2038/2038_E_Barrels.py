# Contest 2038, Problem E: Barrels
# URL: https://codeforces.com/contest/2038/problem/E

import sys
from collections import deque

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
        if len(dq) > 1 and (x == 0 or (h[x - 1] >= h[y])):
            if tmp >= (h[y] - dq[-1][0]) * l:
                tmp -= (h[y] - dq[-1][0]) * l
                dq.pop()
                last_val, (last_x, last_y) = dq[-1]
                dq[-1] = (last_val, (x, last_y))
            else:
                new_val = dq[-1][0] + tmp / l
                dq[-1] = (new_val, (x, y))
                tmp = 0
        else:
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