# Contest 5, Problem D: Follow Traffic Rules
# URL: https://codeforces.com/contest/5/problem/D

import math

a, v = list(map(int, input().split(" ")))
l, d, w = list(map(int, input().split(" ")))
# stage 1, to check point
if v > w and (2 * v * v - w * w) / 2 / a < d:
    # case acc->stable->dec
    t0 = (d - (2 * v * v - w * w) / 2 / a) / v + (2 * v - w) / a
    v1 = w
elif v > w and w * w / a / 2 < d:
    # case acc->dec
    v_max = math.sqrt(0.5 * (w * w + 2 * a * d))
    t0 = (2 * v_max - w) / a
    v1 = w
elif v > w:
    v1 = math.sqrt(2 * a * d)
    t0 = math.sqrt(2 * d / a)
elif v * v / a / 2 < d:
    v1 = v
    t0 = (d - v * v / a / 2) / v + v / a
else:
    v1 = math.sqrt(2 * a * d)
    t0 = math.sqrt(2 * d / a)
# stage 2 to dest
if v1 < v:
    if (v**2 - v1**2) / 2 / a < (l - d):
        t1 = (v - v1) / a + (l - d - ((v**2 - v1**2) / 2 / a)) / v
    else:
        t1 = (-v1 + math.sqrt(v1**2 + 2 * a * (l - d))) / a
else:
    t1 = (l - d) / v

print(round(t0 + t1, 8))
