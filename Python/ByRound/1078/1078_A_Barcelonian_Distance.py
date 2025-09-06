# Contest 1078, Problem A: Barcelonian Distance
# URL: https://codeforces.com/contest/1078/problem/A

import sys
input = sys.stdin.buffer.readline

from math import hypot

def worstCase(coordinate1, coordinate2):
    return abs(coordinate2[0] - coordinate1[0]) + abs(coordinate2[1] - coordinate1[1])

a, b, c = map(int, input().split())
x1, y1, x2, y2 = map(int, input().split())
coor1, coor2  = (x1, y1), (x2, y2)
res = worstCase(coor1, coor2)
if a and b:
    range1 = [(x1, (-c - a*x1)/b), ((-c - b*y1)/a, y1)]
    range2 = [(x2, (-c - a*x2)/b), ((-c - b*y2)/a, y2)]
    for upper in range1:
        for lower in range2:
            res = min(res, worstCase(coor1, upper) + worstCase(coor2, lower) + hypot(upper[0]-lower[0], upper[1]-lower[1]))
print("%.10f" %res)
