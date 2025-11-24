# Problem: CF 1822 G1 - Magic Triples (Easy Version)
# https://codeforces.com/contest/1822/problem/G1

"""
Magic Triples Problem (Easy Version)

Algorithm:
- For each element a[i], we look for valid triples (i,j,k) such that:
  a[i] * b = a[j] and a[j] * b = a[k] for some positive integer b.
- This implies a[k] = a[i] * b^2, which means a[k]/a[i] is a perfect square.
- For each element a[i], we:
  1. Find how many times it appears consecutively (grouping).
  2. Check if there exist elements a[j] = a[i] * b and a[k] = a[i] * b^2.
  3. Count combinations using the grouping counts.
- Uses sorting, binary search with bisect_left, and square root checks.
- Time complexity: O(n * sqrt(max(a)) * log n)
- Space complexity: O(n)

Techniques:
- Sorting + grouping
- Binary search to find next elements
- Square root math to validate triple patterns
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
from bisect import bisect_left
from math import isqrt

inf = 2 * 10**9 + 646


def solve646():
    n = int(input())
    a = list(map(int, input().split()))
    a = sorted(a)
    nxt = [0] * n
    r = 0
    for i in range(n):
        while r < n and a[i] == a[r]:
            r += 1
        nxt[i] = r
    a.append(inf)
    nxt.append(n)

    def add(i, j, k):
        # Calculates number of combinations for triple (i, j, k) based on how many times each element appears
        if i == j == k:
            # All three indices refer to same element
            x = nxt[i] - i
            return x * (x - 1) * (x - 2)
        ci, cj, ck = nxt[i] - i, nxt[j] - j, nxt[k] - k
        t = ci * cj if a[i] < a[j] else ci * (ci - 1)
        if a[j] < a[k]:
            t *= ck
        else:
            t *= cj - 1
        return t

    mx = max(a)
    res = i = 0
    while i < n:
        x = a[i]
        if nxt[i] - i > 2:
            # If the same value occurs more than 2 times, count triplets where all are same
            res += add(i, i, i)
        b, r = 2, mx // x
        while b <= r and x * b * b <= mx:
            xj, xk = x * b, x * b * b
            ij = bisect_left(a, xj, lo=nxt[i], hi=n)
            if a[ij] == xj:
                ik = bisect_left(a, xk, lo=nxt[ij], hi=n)
                b += 1
                if a[ik] == xk:
                    # Found a valid magic triple
                    res += add(i, ij, ik)
                else:
                    # Not exact match, update 'b' based on square root approximation
                    b = max(b, 1 + isqrt(a[ik] // x - 1))
            else:
                # No such intermediate value, increase b appropriately
                b = max(b + 1, a[ij] // x)
        i = nxt[i]
    return res


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/CodeForces/