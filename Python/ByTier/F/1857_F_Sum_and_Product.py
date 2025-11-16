# Problem: CF 1857 F - Sum and Product
# https://codeforces.com/contest/1857/problem/F

"""
Algorithm: Sum and Product Pairs
Techniques: Mathematical approach using quadratic formula, hash map for counting

Time Complexity: O(n + q * sqrt(D)) where D = x^2 - 4*y, n is the size of array, q is number of queries
Space Complexity: O(n) for storing frequency counts in hash map

This solution uses the fact that if two numbers a and b satisfy:
a + b = x and a * b = y,
then they are roots of the quadratic equation t^2 - x*t + y = 0.
Using the quadratic formula, we derive the possible values for a and b.
We then count how many times these values appear in the array and compute valid pairs.
"""

import math
import sys
from collections import defaultdict

input = sys.stdin.readline


def sumprod():
    int(input())
    a = list(map(int, input().split()))
    q = int(input())
    cnt = defaultdict(int)
    for v in a:
        cnt[str(v)] += 1
    l = []
    for i in range(q):
        x, y = map(int, input().split())
        d = x * x - 4 * y
        if d < 0:
            l.append(0)
            continue
        dd = math.isqrt(d)
        if dd * dd != d:
            l.append(0)
            continue
        num1 = (x + dd) // 2
        num2 = (x - dd) // 2
        if num1 == num2:
            coun = cnt[str(num1)]
            final = coun * (coun - 1) // 2
        else:
            final = cnt[str(num1)] * cnt[str(num2)]
        l.append(final)
    print(*l)


t = int(input())
for i in range(t):
    sumprod()


# https://github.com/VaHiX/CodeForces/