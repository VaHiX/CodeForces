# Problem: CF 2094 F - Trulimero Trulicina
# https://codeforces.com/contest/2094/problem/F

"""
F. Trulimero Trulicina

Purpose:
This code generates an n×m grid filled with integers from 1 to k such that:
- Each integer appears exactly (n*m)/k times.
- No two adjacent cells (sharing an edge) have the same integer.

Algorithm:
The approach uses a cyclic filling strategy where we iterate through rows and columns,
assigning values in a pattern that ensures no two adjacent cells have the same value.
A key insight is to utilize modular arithmetic to control the sequence and avoid
adjacent duplicates. A small adjustment with 'idx' helps fine-tune the sequence for
specific edge cases.

Time Complexity: O(n * m)
Space Complexity: O(1) - Only using a constant amount of extra space (excluding output).

Techniques:
- Modular arithmetic for cycling through values.
- Row-wise iteration to fill grid systematically.
- Adjustment with 'idx' for handling special cases in modulo operation.
"""

import sys

input = lambda: sys.stdin.readline()
t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    idx = 0
    for i in range(n):
        for j in range(m):
            if m % k:  # If m is not divisible by k
                print((i * m + j) % k + 1, end=" ")  # Simple cyclic pattern
            else:
                print((i * m + j + idx) % k + 1, end=" ")  # Adjusted pattern to avoid adjacent duplicates
        idx += 1  # Increment index to shift next row's values
        print()


# https://github.com/VaHiX/codeForces/