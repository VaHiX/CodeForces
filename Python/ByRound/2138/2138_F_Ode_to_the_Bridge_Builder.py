# Problem: CF 2138 F - Ode to the Bridge Builder
# https://codeforces.com/contest/2138/problem/F

"""
F. Ode to the Bridge Builder

This problem involves constructing a sequence of triangles in a 2D plane to reach a target point (p, q) 
using at most m operations. Each operation adds one new point and two new line segments, forming a triangle.

Algorithms/Techniques:
- Geometric constructions using rotation and vector addition
- Iterative point generation along a path towards (p, q)
- Special handling of cases where m is even or odd
- Use of complex numbers for rotation calculations

Time Complexity: O(m) where m is the number of operations; each operation performs constant time work.
Space Complexity: O(m) to store intermediate points and operations.

The solution constructs a path by:
1. For small enough (p,q) with respect to √15, it uses an intersection-based approach to find a good point.
2. For larger (p,q), it constructs a sequence of points by rotating and adding vectors,
   simulating a spiral or zigzag path towards the target point.
"""

import math


def rotate(x, y):
    # Rotates vector (x,y) by 60 degrees counterclockwise.
    x1 = x[0]
    y1 = x[1]
    x2 = y[0]
    y2 = y[1]
    return (
        (x1 + x2) / 2 + 3**0.5 * (y2 - y1) / 2,
        (y1 + y2) / 2 + 3**0.5 * (x1 - x2) / 2,
    )


def add(x, y):
    # Adds two 2D vectors.
    return (x[0] + y[0], x[1] + y[1])


def intersect(r, a, b):
    # Finds intersection point of a circle and a line for triangle construction.
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
    # Maps point to complex number space for rotation.
    a = complex(x, y)
    a /= complex(0.5, 3**0.5 / 2)
    a -= 1
    return [a.real, a.imag]


def g(x, y):
    # Maps back from complex space after rotation.
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
                # Special case for the second point
                print(1, 3, 2 * x, 2 * y)
            else:
                print(i + 1, i + 2, (i + 1) * x, (i + 1) * y)
        print(m, m + 1, p, q)
    else:
        if m % 2 == 0:
            # Even case: generate points iteratively
            r = math.sqrt(p * p + q * q)
            x = p / r
            y = q / r
            l = [[1, 2, (3**0.5 / 2, 1 / 2)], [1, 3, (x, y)]]  # Pre-init points
            for i in range(1, m - 1):
                u = i + 2  # Next point identifier
                v = i + 3  # Another point identifier
                if i == m - 2:
                    point = (p, q)  # Target point
                elif i == 1:
                    # Add previous two points for rotation
                    point = add(l[0][2], l[1][2])
                else:
                    # Use vector addition property to generate point
                    point = (
                        l[i - 1][2][0] + l[i][2][0] - l[i - 2][2][0],
                        l[i - 1][2][1] + l[i][2][1] - l[i - 2][2][1],
                    )
                l.append([u, v, point])
            print(len(l))
            for i in l:
                print(i[0], i[1], i[2][0], i[2][1])
        else:
            # Odd case: adjust target and compute similarly
            p -= 3**0.5 / 2  # Shift x to account for initial offset
            q -= 1 / 2        # Shift y to account for initial offset
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


# https://github.com/VaHiX/codeForces/