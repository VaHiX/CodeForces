# Problem: CF 2007 B - Index and Maximum Value
# https://codeforces.com/contest/2007/problem/B

"""
B. Index and Maximum Value

Algorithm/Technique: 
- Direct simulation with optimization using maxo variable to track current maximum
- For each operation, we check if the current maximum falls within the range [l, r]
  and update it accordingly without modifying the entire array

Time Complexity: O(n + m) per test case
Space Complexity: O(1) excluding input/output storage

The algorithm maintains a single variable `maxo` that tracks the current maximum value,
avoiding the need to recompute the maximum after each operation on the full array.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    maxo = max(a)  # Track current maximum value
    out = []
    for j in range(m):
        c, l, r = input().split()
        l, r = int(l), int(r)
        # If the current max lies in [l, r], update it based on operation type
        if l <= maxo <= r:
            maxo += 1 - 2 * int(c == "-")  # Add 1 for '+' or subtract 1 for '-'
        out.append(maxo)  # Store updated maximum
    print(*out)


# https://github.com/VaHiX/codeForces/