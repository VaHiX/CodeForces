# Problem: CF 630 Q - Pyramids
# https://codeforces.com/contest/630/problem/Q

from math import pi, sin, sqrt


def volume(a, n):
    # Calculate the circumradius x of the regular polygon base
    x = a / (2 * sin(pi / n))
    # Calculate the base area S of the pyramid
    S = sqrt(x * x - a * a / 4) * a / 2 * n
    # Calculate the height h of the pyramid
    h = sqrt(a * a - x * x)
    # Return the volume of the pyramid: (1/3) * base_area * height
    return S * h / 3


l3, l4, l5 = map(int, input().split())
print(volume(l3, 3) + volume(l4, 4) + volume(l5, 5))


# https://github.com/VaHiX/CodeForces/