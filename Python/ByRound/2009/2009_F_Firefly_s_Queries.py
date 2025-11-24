# Problem: CF 2009 F - Firefly's Queries
# https://codeforces.com/contest/2009/problem/F

"""
F. Firefly's Queries

Purpose:
This code handles multiple queries on a cyclic shift concatenated array `b` derived from input array `a`.
For each query, it computes the sum of elements in a subarray of `b`.

Algorithms/Techniques:
- Prefix sum for efficient range sum queries.
- Modular arithmetic to handle cyclic shifts.
- Preprocessing: Build prefix sums for fast query evaluation.

Time Complexity: O(n + q) per test case
Space Complexity: O(n) per test case

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: n (length of array), q (number of queries)
  - Second line: n integers representing array a
  - Next q lines: l, r for each query

Output Format:
- For each query, output the sum of subarray b[l..r]
"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())
P = print


def f(i):
    # Helper function to access array with cyclic indexing
    if i > n:
        return a[i - n] + a[n]
    return a[i]


for _ in range(int(R())):
    n, q = S()
    a = [0] + [*S()]  # Add dummy element at index 0 for easier prefix sums
    
    # Build prefix sum array
    for i in range(n):
        a[i + 1] += a[i]
    
    for _ in range(q):
        l, r = S()  # Query range [l, r]
        x, y = divmod(l - 1, n)  # x = full cycles, y = offset within cycle
        z, w = divmod(r - 1, n)  # z = full cycles, w = offset within cycle
        
        # Compute the result using prefix sums and modular arithmetic
        P(a[n] * (z - x - 1) + f(z + w + 1) - f(z) - f(x + y) + f(x + n))


# https://github.com/VaHiX/codeForces/