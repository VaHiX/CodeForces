# Problem: CF 772 A - Voltage Keepsake
# https://codeforces.com/contest/772/problem/A

"""
Code Purpose:
This code solves the problem of determining the maximum amount of time n devices can be used simultaneously,
given their power consumption rates, initial power stored, and a charger with fixed power output.
It uses binary search on the time variable to find the maximum sustainable time before any device runs out of power.
The charging strategy is optimized by choosing which device to charge at each moment to maximize usage time.

Algorithms/Techniques:
- Binary Search: On the time variable to find the maximum sustainable time.
- Greedy Charging Strategy: At each step, determine how much power must be supplied via charging
  to meet the power deficit of all devices.

Time Complexity: O(n * log(T)) where T is the upper bound on time (approx. ts / (total - p))
Space Complexity: O(n) for storing device parameters

"""

import sys

RI = lambda: int(sys.stdin.readline().strip())
RS = lambda: sys.stdin.readline().strip()
RII = lambda: map(int, sys.stdin.readline().strip().split())
RILIST = lambda: list(RII())
mx = lambda x, y: x if x > y else y
mn = lambda x, y: y if x > y else x
eps = 10**-6
n, p = RII()
a, b = [], []
total = ts = 0
for _ in range(n):
    x, y = RII()
    a.append(x)
    b.append(y)
    total += x
    ts += y
if p >= total:
    print(-1)
    exit()
l, r = 0, ts / (total - p) + 1


def check(mid):
    # Calculate total power needed to sustain all devices for 'mid' seconds
    t = 0
    for i, (x, y) in enumerate(zip(a, b)):
        t += mx(0, mid * x - y)  # Power deficit per device if current power is insufficient
    return mid * p >= t  # Check if charger can supply enough power


ans = -1
while l + eps < r:
    mid = (l + r) / 2
    if check(mid):
        l = mid
        ans = mid
    else:
        r = mid
print(ans)


# https://github.com/VaHiX/CodeForces/