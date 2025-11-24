# Problem: CF 2002 C - Black Circles
# https://codeforces.com/contest/2002/problem/C

"""
C. Black Circles
Algorithm: Geometric distance comparison
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The problem involves determining if a path exists from a start point to a target point 
without touching any expanding circles. Each circle starts with radius 0 and grows at 1 unit/second.
At any given time t, the circle centered at (xi, yi) has radius t.

We must check whether there's a valid path such that at no point in time does the 
path intersect with the circumference of any circle.

Key Insight:
- At time t:
  - Distance from start to center of circle = d_start
  - Distance from target to center of circle = d_target  
  - If d_target <= d_start, then the target point can be reached before the circle 
    reaches that point (or it is already inside), so we cannot avoid the circle.
- This check is sufficient because:
  - The only way a circle can block your path is if it touches or enters your path
  - If distance from start to center > distance from target to center, then:
    * The target point will reach the circle later than the start point, 
      meaning we have time to pass by without touching.
  - Otherwise, if d_target <= d_start, then at time = d_target,
    the circle's radius would be d_target and will touch or block our path.

We only need to compare distances, not simulate movement through time.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    l = []
    for i in range(n):
        a, b = map(int, input().split())
        l.append([a, b])
    xs, ys, xf, yf = map(int, input().split())
    ans = "YES"
    for i in range(n):
        ai, bi = l[i]
        # Check if target is closer to circle than start.
        # If so, the circle will touch or block the path.
        if (xf - ai) ** 2 + (yf - bi) ** 2 <= (xs - xf) ** 2 + (ys - yf) ** 2:
            ans = "NO"
            break
    print(ans)


# https://github.com/VaHiX/codeForces/