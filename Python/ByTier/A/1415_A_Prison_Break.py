# Problem: CF 1415 A - Prison Break
# https://codeforces.com/contest/1415/problem/A

# ==================================================================
# Problem: Prison Break
# Algorithm: Mathematical calculation of maximum distance from any cell to the escape tunnel
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==================================================================

import sys

input = sys.stdin.buffer.readline
t = int(input())
for i in range(t):
    n, m, r, c = [int(x) for x in input().split()]
    # Calculate the maximum Manhattan distance from any cell to the escape tunnel at (r, c)
    # For rows: max distance is either from top row (n-r) or bottom row (r-1)
    # For columns: max distance is either from leftmost column (m-c) or rightmost column (c-1)
    sys.stdout.write(f"{max(n-r, r-1)+max(m-c, c-1)}\n")


# https://github.com/VaHiX/codeForces/