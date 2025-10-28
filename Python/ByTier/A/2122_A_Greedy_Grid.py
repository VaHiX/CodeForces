# Problem: CF 2122 A - Greedy Grid
# https://codeforces.com/contest/2122/problem/A

# ******************************************************************************
# Problem: Grid with No Greedy Path Achieving Maximum Value
# Purpose: Determine if there exists an n×m grid of nonnegative integers such that
#          no greedy path (which always moves to the greater neighbor) achieves
#          the maximum down/right path value.
#
# Algorithm/Techniques:
# - Greedy Grid Analysis
# - Mathematical Observation
# - Case-based Logic for Grid Feasibility
#
# Time Complexity: O(1) per test case — constant time due to mathematical analysis.
# Space Complexity: O(1) — no additional space used beyond input processing.
# ******************************************************************************

for s in [*open(0)][1:]:  # Read all lines from stdin except first (test cases count)
    a, b = sorted(map(int, s.split()))  # Parse and sort the dimensions
    # The condition checks:
    # - If either dimension is less than 2 (small grids) -> impossible to avoid greedy path
    # - If the smaller dimension is less than 3 -> impossible for larger grid
    # The string "YNEOS"[b < 3 or a < 2 :: 2] maps boolean to "YES"/"NO"
    print("YNEOS"[b < 3 or a < 2 :: 2])


# https://github.com/VaHiX/codeForces/