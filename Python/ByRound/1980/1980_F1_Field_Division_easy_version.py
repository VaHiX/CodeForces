# Problem: CF 1980 F1 - Field Division (easy version)
# https://codeforces.com/contest/1980/problem/F1

"""
Algorithm: Greedy approach to find maximum area Alice can get.
Approach:
1. For each column, we track the highest row (from top) where a fountain exists.
2. We process columns in ascending order.
3. For each column, if the fountain is higher than the current row (i.e. a better path),
   we update our path and calculate area.
4. We also keep track of which fountain, if given to Alice, increases her area.

Time Complexity: O(k log k) due to sorting of columns.
Space Complexity: O(k) for storing fountain locations and result array.
"""

import sys
from collections import defaultdict

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


for _ in range(inp()):
    n, m, k = inlt()
    # Dictionary to store the maximum row number for each column
    c_max = defaultdict(lambda: (-1, -1))
    # Array to store whether giving fountain i to Alice increases her area
    a = [0] * k
    
    # Process each fountain
    for i in range(k):
        r, c = inlt()
        # Update the maximum row for column c
        if c_max[c - 1][0] < r - 1:
            c_max[c - 1] = (r - 1, i)

    # Get minimum column index among all fountains
    mn_c = min(c_max.keys())

    # Initialize tracking variables for path
    r = -1  # Current row
    c = 0   # Current column
    
    # Initialize area calculation
    area = 0

    # Handle first column case
    if mn_c == 0:
        # Get maximum row in first column
        mn_r = c_max[0][0]
        a[c_max[0][1]] = 1  # Mark this fountain as contributing to increase
        r = mn_r
        c = mn_c

    # Process all columns except first one
    for f_c in sorted(c_max.keys()):
        if f_c == 0:
            continue

        # Get maximum row for this column
        f_r = c_max[f_c][0]

        # If this column's fountain is higher than current row, we can add area
        if f_r <= r:
            continue

        # Mark this fountain as beneficial to Alice
        a[c_max[f_c][1]] = 1
        # Add area of rectangle formed between previous row and new row
        area += (f_c) * (f_r - r)
        r = f_r
        c = f_c

    # Add final area from remaining rows to bottom of field
    area += m * (n - 1 - r)
    print(area)
    print(*a)


# https://github.com/VaHiX/CodeForces/