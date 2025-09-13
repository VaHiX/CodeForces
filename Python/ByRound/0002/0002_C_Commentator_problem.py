# Contest 2, Problem C: Commentator problem
# URL: https://codeforces.com/contest/2/problem/C

import math


# return a(x^2 + y^2) + bx + cy + d = 0
def calc(arr1, arr2):
    x1, y1, r1 = arr1
    x2, y2, r2 = arr2
    if r1 == r2:  # result is a line if r1 == r2
        return [0, x2 - x1, y2 - y1, (x1 * x1 + y1 * y1 - x2 * x2 - y2 * y2) / 2]
    else:  # result is a circle
        k = r2 / r1
        x3, y3 = (k * x1 + x2) / (k + 1), (k * y1 + y2) / (
            k + 1
        )  # coordination of intersection points of the result circle and line AB
        x4, y4 = (k * x1 - x2) / (k - 1), (k * y1 - y2) / (k - 1)
        cx, cy = (x3 + x4) / 2, (y3 + y4) / 2  # coorination of the center
        return [
            1,
            -2 * cx,
            -2 * cy,
            cx * cx + cy * cy - (cx - x3) ** 2 - (cy - y3) ** 2,
        ]


def solve2(a, b, c):
    delta = b * b - 4 * a * c
    if delta < 0:
        return []
    if delta == 0:
        return [-b / a / 2]
    return [(-b + math.sqrt(delta)) / a / 2, (-b - math.sqrt(delta)) / a / 2]


def ll(f1, f2):
    a1, b1, c1 = f1
    a2, b2, c2 = f2
    return (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1), (c2 * a1 - c1 * a2) / (
        b1 * a2 - b2 * a1
    )


def lc(f1, f2):
    res = []
    if f1[1] == f1[2] == 0:
        return res
    elif f1[1] == 0:
        y = -f1[3] / f1[2]
        for x in solve2(1, f2[1], f2[3] + y * y + f2[2] * y):
            res.extend([x, y])
    elif f2[1] == 0:
        x = -f1[3] / f1[1]
        for y in solve2(1, f2[2], f2[3] + x * x + f2[1] * x):
            res.extend([x, y])
    else:
        k = -f1[1] / f1[2]
        b = -f1[3] / f1[2]
        for x in solve2(
            1 + k * k, f2[1] + k * b * 2 + f2[2] * k, f2[3] + b * b + f2[2] * b
        ):
            res.extend([x, k * x + b])
    return res


def fmt(arr):
    res = []
    for x in arr:
        s = str(round(x, 5))
        idx = s.find(".")
        if idx == -1:
            res.append(s + ".00000")
        else:
            res.append(s + "0" * (6 + idx - len(s)))
    return res


mat = [[int(x) for x in input().split(" ")] for _ in range(3)]
mat.sort(key=lambda x: x[2])  # sort by radius
f1 = calc(mat[0], mat[1])
f2 = calc(mat[1], mat[2])
if f1[0] == f2[0] == 0:
    res = ll(f1[1:], f2[1:])
    print(" ".join(fmt(res)))
else:
    if f1[0] == 0:
        res = lc(f1, f2)
    elif f2[0] == 0:
        res = lc(f2, f1)
    else:
        res = lc([f1[i] - f2[i] for i in range(4)], f2)
    if len(res) == 2:
        print(" ".join(fmt(res)))
    elif len(res) == 4:
        x1, y1, x2, y2 = res
        x0, y0 = mat[0][:2]
        if (x1 - x0) ** 2 + (y1 - y0) ** 2 < (x2 - x0) ** 2 + (y2 - y0) ** 2:
            print(" ".join(fmt(res[:2])))
        else:
            print(" ".join(fmt(res[2:])))
