# Problem: CF 2148 B - Lasers
# https://codeforces.com/contest/2148/problem/B

"""
B. Lasers

Purpose:
This problem involves finding the minimum number of laser crossings when moving from (0,0) to (x,y)
on a 2D plane with horizontal and vertical lasers obstructing paths.

Key insights:
- To move from (0,0) to (x,y), we need to traverse through horizontal and vertical lasers.
- The optimal path will cross lasers optimally, avoiding unnecessary detours.
- Horizontal lasers are at y = a_i, and vertical lasers are at x = b_i.
- We want to count the minimum crossings — that is, how many distinct horizontal and vertical lasers
  must be crossed on any valid path.

Algorithm:
- The minimum number of crossings is equal to the minimum of:
    - Number of horizontal lasers intersected by a vertical path from (0,0) to (x,y)
    - Number of vertical lasers intersected by a horizontal path from (0,0) to (x,y)

However, since we're moving from (0,0) to (x,y) and both axes are fully accessible:
- The minimal number of crossings is exactly the number of distinct horizontal lasers
  that separate (0,0) to y, plus the number of vertical lasers separating (0,0) to x.
- More specifically:
    - Count how many a_i values are between 0 and y such that the path from (0,0) enters a region
      below a_i. Since a_i is sorted in ascending order, we can do prefix checks.
    - And similarly for b_i values.

But observing more carefully:
- The minimal number of crossings is the number of horizontal lasers passed when going from 0 to y,
  plus the number of vertical lasers passed when going from 0 to x.
- Since the path goes from (0,0) to (x,y) in a continuous curve and the goal is minimum crossings,
  we can take a 'stepwise' approach:
    - For horizontal lasers (sorted ascending), count how many are crossed as we go from y=0 to y=y.
    - Same for vertical lasers.

Time Complexity: 
O(n log n + m log m) for binary search (or O(n + m) if we process sorted arrays directly).

Space Complexity:
O(1) extra space for computation, not counting input storage.
"""

for _ in range(int(input())):
    n, m, x, y = map(int, input().split())
    # Read the horizontal lasers' y-coordinates
    a = list(map(int, input().split()))
    # Read the vertical lasers' x-coordinates
    b = list(map(int, input().split()))
    
    # The minimum number of crossings is:
    # number of horizontal lasers passed (between 0 and y) + 
    # number of vertical lasers passed (between 0 and x)
    # Since lasers are already sorted in ascending order,
    # we count how many a_i < y and b_i < x
    
    # Count of horizontal lasers below y
    h_crossings = 0
    for i in range(n):
        if a[i] < y:
            h_crossings += 1
        else:
            break  # Since they are sorted increasingly, no need to continue

    # Count of vertical lasers to the left of x
    v_crossings = 0
    for i in range(m):
        if b[i] < x:
            v_crossings += 1
        else:
            break  # Similarly, they're sorted increasingly

    print(h_crossings + v_crossings)


# https://github.com/VaHiX/codeForces/