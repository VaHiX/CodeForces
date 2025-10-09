# Contest 8, Problem D: Two Friends
# URL: https://codeforces.com/contest/8/problem/D

import math


def dist(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)


def chk(r1):  # r1 = |PH|, r2 = |PS|
    r2 = r1 + s2 - s1
    k = -(x2 - x3) / (y2 - y3)  # 2 circles => secant: y = kx + t
    t = (r2 * r2 - r1 * r1 + x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3) / 2 / (y2 - y3)
    a = 1 + k * k  # secant & circle1 => ax2 + bx + c = 0
    b = -2 * x2 + 2 * k * (t - y2)
    c = x2 * x2 + (t - y2) * (t - y2) - r1 * r1
    delta = math.sqrt(
        b * b - 4 * a * c
    )  # not sure if very small negative value is possible
    xp1 = (-b + delta) / 2 / a
    yp1 = k * xp1 + t
    xp2 = (-b - delta) / 2 / a
    yp2 = k * xp2 + t
    d1 = dist(xp1, yp1, x1, y1)
    d2 = dist(xp2, yp2, x1, y1)
    # but if P is not in triangle |CHS|, should return True
    # is seems that all 3 vertexes should be checked
    if round(d1 - d2, 5) <= 0:
        if (
            (a12 * xp1 + b12 * yp1 + c12) * v3 < 0
            or (a13 * xp1 + b13 * yp1 + c13) * v2 < 0
            or (a23 * xp1 + b23 * yp1 + c23) * v1 < 0
        ):
            return True
    else:
        if (
            (a12 * xp2 + b12 * yp2 + c12) * v3 < 0
            or (a13 * xp2 + b13 * yp2 + c13) * v2 < 0
            or (a23 * xp2 + b23 * yp2 + c23) * v1 < 0
        ):
            return True
    # check |CP| <= |CP| + d0 = s1 - |PH|
    return min(d1, d2) <= s1 - r1


def bs(l, r):
    while r - l >= 0.00001:
        m = (l + r) / 2
        if chk(m):
            r = m
        else:
            l = m
    return m


t1, t2 = [int(x) for x in input().split(" ")]
x1, y1 = [int(x) for x in input().split(" ")]
x2, y2 = [int(x) for x in input().split(" ")]
x3, y3 = [int(x) for x in input().split(" ")]
if y2 == y3:
    x1, y1 = y1, x1
    x2, y2 = y2, x2
    x3, y3 = y3, x3
d1 = dist(x1, y1, x2, y2)  # CH
d2 = dist(x1, y1, x3, y3)  # CS
d3 = dist(x3, y3, x2, y2)  # SH
s1 = d1 + t2
s2 = d2 + t1
diff = s1 - s2
a12, b12 = y2 - y1, x1 - x2  # line CH ax + by + c= 0
c12 = -a12 * x1 - b12 * y1
a13, b13 = y3 - y1, x1 - x3  # line CS
c13 = -a13 * x1 - b13 * y1
a23, b23 = y3 - y2, x2 - x3  # line SH
c23 = -a23 * x2 - b23 * y2
v1 = a23 * x1 + b23 * y1 + c23
v2 = a13 * x2 + b13 * y2 + c13
v3 = a12 * x3 + b12 * y3 + c12
if (
    s1 >= d2 + d3 or s2 >= s1 + d3
):  # they follow the same route C...CSH or C...CH & C...CHSH
    print("{:.5f}".format(min(s1, s2 + d3)))
elif (x3 - x1) * (y2 - y1) == (x2 - x1) * (y3 - y1):  # CHS lie on the same line
    print("{:.5f}".format((t1 + t2) / 2 + (d1 if round(d2 - d1 - d3, 0) == 0 else 0)))
else:  # they walk circles around the cinema for d0 >= 0, and part ways at P
    # where P lies in triangle CHS, and |CP| + |PH| + d0 = d1 + t2, |CP| + |PS| + d0 + d3 = d2 + d3 + t1
    # we need to maximize d0 + |CP|
    # as P moves away from |SH|, |PH| increases monotonely
    print(
        "{:.5f}".format(s1 - bs((d3 + diff) / 2, max(d1, d3)))
    )  # find min |PH|; min: P on |SH|, max: P on |CS|
