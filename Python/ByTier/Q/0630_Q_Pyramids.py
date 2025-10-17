# Contest 630, Problem Q: Pyramids
# URL: https://codeforces.com/contest/630/problem/Q

from math import sin, cos, pi, sqrt


def volume(a, n):
    x = a / (2 * sin(pi / n))
    S = sqrt(x * x - a * a / 4) * a / 2 * n
    h = sqrt(a * a - x * x)
    return S * h / 3


l3, l4, l5 = map(int, input().split())
print(volume(l3, 3) + volume(l4, 4) + volume(l5, 5))
