# Contest 280, Problem A: Rectangle Puzzle
# URL: https://codeforces.com/contest/280/problem/A

import math

h, w, a = map(float, input().split())
if a > 90.0:
    a = 180.0 - a
if h > w:
    h, w = w, h
a = a / 180 * math.pi
ans = 0
if a / 2 >= math.atan(h / w):
    ans = h * h / math.sin(a)
else:
    ans = h * w / math.cos(a) - (h * h + w * w) / 2 * math.tan(a / 2) / math.cos(a)
print(ans)  # 1691666829.9459567
