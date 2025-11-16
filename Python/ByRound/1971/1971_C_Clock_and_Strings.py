# Problem: CF 1971 C - Clock and Strings
# https://codeforces.com/contest/1971/problem/C

"""
Problem: Determine if two strings connecting points on a clock intersect.
Algorithm/Technique: Modular arithmetic and comparison of relative positions.
Time Complexity: O(1) per test case.
Space Complexity: O(1) for variables, O(t) for output storage where t is number of test cases.

The approach is to fix one point (a) as the origin and compute the relative positions of the other points.
If both other points lie on the same side of the first point (when moving clockwise), the strings do not intersect.
Otherwise, they do intersect.
"""

import sys

input = sys.stdin.readline


def solve():
    a, b, c, d = map(int, input().split())
    # Normalize positions relative to 'a'
    b = (b - a) % 12
    c = (c - a) % 12
    d = (d - a) % 12

    # If both c and d are on the same side of b (when going clockwise from a),
    # then the strings do not intersect
    if (c > b and d > b) or (c < b and d < b):
        return "NO"
    else:
        return "YES"


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/