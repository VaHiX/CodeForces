# Problem: CF 2026 A - Perpendicular Segments
# https://codeforces.com/contest/2026/problem/A

"""
Code Purpose:
This code solves the problem of finding two perpendicular line segments AB and CD
in a coordinate plane such that:
- All coordinates are integers within bounds [0, X] and [0, Y]
- Both segments have length at least K
- The segments are perpendicular (as lines, not necessarily intersecting)

Algorithm/Techniques:
- The approach uses a simple geometric construction based on the fact that
  two lines with slopes m1 and m2 are perpendicular if m1 * m2 = -1.
  Here, we use simple integer slopes: one horizontal (0,1), one vertical (1,0).
- We place one segment from (0,0) to (m,m) which has length sqrt(2*m^2)
  where m = min(X,Y). A second segment from (m,0) to (0,m) also has length
  sqrt(2*m^2) and is clearly perpendicular.
- The solution guarantees that K <= 1414, and given that X,Y <= 1000,
  we ensure existence of solution via careful selection of m.

Time Complexity: O(1) - constant time due to fixed computations per test case.
Space Complexity: O(1) - only using fixed-size variables regardless of input size.
"""

for _ in range(int(input())):
    x, y, k = map(int, input().split())
    m = min(x, y)
    print(0, 0, m, m)
    print(m, 0, 0, m)


# https://github.com/VaHiX/CodeForces/