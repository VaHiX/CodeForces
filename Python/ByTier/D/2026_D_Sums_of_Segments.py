# Problem: CF 2026 D - Sums of Segments
# https://codeforces.com/contest/2026/problem/D

"""
Problem: Sums of Segments
Algorithm: Preprocessing with prefix sums and binary search for query optimization
Time Complexity: O(n^2) preprocessing, O(log n) per query
Space Complexity: O(n^2) for storing precomputed values

The problem involves:
1. Computing all segment sums of an array a
2. Storing them in a specific order in array b
3. Answering multiple range sum queries on b efficiently

We use preprocessing with prefix sums to compute values efficiently.
Binary search is used to determine the segment indices in the b array.
"""

import sys

input = lambda: sys.stdin.readline().strip()
n = int(input())
a = list(map(int, input().split()))

# Prefix sum of array a
b = [0] * (n + 1)
for i in range(1, n + 1):
    b[i] = b[i - 1] + a[i - 1]

# Prefix sum of prefix sums
c = [0] * (n + 1)
for i in range(1, n + 1):
    c[i] = c[i - 1] + b[i]

# Precompute d for optimized range sum queries
d = [0] * (n + 1)
for i in range(1, n + 1):
    d[i] = d[i - 1] + c[n] - c[i - 1] - b[i - 1] * (n - i + 1)

q = int(input())
for i in range(q):
    l, r = map(int, input().split())
    l1 = 0
    r1 = n + 1
    while r1 - l1 > 1:
        m = (r1 + l1) // 2
        if m * (2 * n - m + 1) // 2 < l:
            l1 = m
        else:
            r1 = m
    l2 = 0
    r2 = n + 1
    while r2 - l2 > 1:
        m = (r2 + l2) // 2
        if m * (2 * n - m + 1) // 2 < r:
            l2 = m
        else:
            r2 = m
    k1 = l - (r1 - 1) * (2 * n - r1 + 2) // 2
    k2 = r - (r2 - 1) * (2 * n - r2 + 2) // 2
    if r1 == r2:
        print(c[k2 + r1 - 1] - c[k1 + r1 - 2] - b[r1 - 1] * (k2 - k1 + 1))
    else:
        print(
            c[n]
            - c[k1 + r1 - 2]
            - b[r1 - 1] * (n - k1 - r1 + 2)
            + c[k2 + r2 - 1]
            - c[r2 - 1]
            - b[r2 - 1] * k2
            + d[r2 - 1]
            - d[r1]
        )


# https://github.com/VaHiX/CodeForces/