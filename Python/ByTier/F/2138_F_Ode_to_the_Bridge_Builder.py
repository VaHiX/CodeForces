# Contest 2138, Problem F: Ode to the Bridge Builder
# URL: https://codeforces.com/contest/2138/problem/F

import math


def rotate(x, y):
    x1 = x[0]
    y1 = x[1]
    x2 = y[0]
    y2 = y[1]
    return (
        (x1 + x2) / 2 + 3**0.5 * (y2 - y1) / 2,
        (y1 + y2) / 2 + 3**0.5 * (x1 - x2) / 2,
    )


def add(x, y):
    return (x[0] + y[0], x[1] + y[1])


def intersect(r, a, b):
    p = 2 * a
    q = 2 * b
    z = 0.25 - r * r - a * a - b * b

    a1 = (q / p) ** 2 + 1
    a2 = 2 * q * z / (p * p)
    a3 = (z / p) ** 2 - r * r
    y = (-a2 - max(0, a2 * a2 - 4 * a1 * a3) ** 0.5) / (2 * a1)
    x = -q / p * y - z / p
    d = 0.5 / ((x - a) ** 2 + (y - b) ** 2) ** 0.5
    return (a + d * (x - a), b + d * (y - b))


def f(x, y):
    a = complex(x, y)
    a /= complex(0.5, 3**0.5 / 2)
    a -= 1
    return [a.real, a.imag]


def g(x, y):
    a = complex(x, y)
    a += 1
    a *= complex(0.5, 3**0.5 / 2)
    return [a.real, a.imag]


for _ in range(int(input())):
    p, q, m = map(int, input().split())
    if q / p < 15**0.5:
        x1 = intersect((m - 1) / 2, p, q)
        p1 = x1[0]
        q1 = x1[1]
        x = p1 / (m - 1)
        y = q1 / (m - 1)
        print(m)
        for i in range(m - 1):
            if i == 1:
                print(1, 3, 2 * x, 2 * y)
            else:
                print(i + 1, i + 2, (i + 1) * x, (i + 1) * y)
        print(m, m + 1, p, q)
    else:
        if m % 2 == 0:
            r = math.sqrt(p * p + q * q)
            x = p / r
            y = q / r
            l = [[1, 2, (3**0.5 / 2, 1 / 2)], [1, 3, (x, y)]]
            for i in range(1, m - 1):
                u = i + 2
                v = i + 3
                if i == m - 2:
                    point = (p, q)
                elif i == 1:
                    point = add(l[0][2], l[1][2])
                else:
                    point = (
                        l[i - 1][2][0] + l[i][2][0] - l[i - 2][2][0],
                        l[i - 1][2][1] + l[i][2][1] - l[i - 2][2][1],
                    )
                l.append([u, v, point])
            print(len(l))
            for i in l:
                print(i[0], i[1], i[2][0], i[2][1])
        else:
            p -= 3**0.5 / 2
            q -= 1 / 2
            r = m // 2
            x = p / r
            y = q / r
            l = [[1, 2, (3**0.5 / 2, 1 / 2)], [1, 3, (x, y)]]
            p += 3**0.5 / 2
            q += 1 / 2
            for i in range(1, m - 1):
                u = i + 2
                v = i + 3
                if i == m - 2:
                    point = (p, q)
                elif i == 1:
                    point = add(l[0][2], l[1][2])
                else:
                    point = (
                        l[i - 1][2][0] + l[i][2][0] - l[i - 2][2][0],
                        l[i - 1][2][1] + l[i][2][1] - l[i - 2][2][1],
                    )
                l.append([u, v, point])
            print(len(l))
            for i in l:
                print(i[0], i[1], i[2][0], i[2][1])
