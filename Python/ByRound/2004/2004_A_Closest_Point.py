# Problem: CF 2004 A - Closest Point
# https://codeforces.com/contest/2004/problem/A

# ====================================================================
# Problem: Closest Point
# Algorithm: Greedy / Interval Analysis
# Time Complexity: O(n) per test case
# Space Complexity: O(1)
# ====================================================================

for l in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip n and empty lines)
    x, y, *r = map(int, l.split())  # Parse input: x=first point, y=second point, r=remaining points
    # Check if the gap between x and y is <= 1 or if there are any other points in range.
    # If so, no valid point can be inserted to make it closest to all.
    print("YNEOS"[y - x < 2 or [] < r :: 2])  # Output result based on condition


# https://github.com/VaHiX/codeForces/