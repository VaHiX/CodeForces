# Problem: CF 2095 G - Definitely a Geometry Problem
# https://codeforces.com/contest/2095/problem/G

"""
G. Definitely a Geometry Problem

Problem Description:
Megumin wants to kill at least k out of n slimes using a single circular explosion spell.
The cost of the spell is proportional to the area of the circle (π * r^2).
We are to find the minimum cost, i.e., minimum area of a circle that covers at least k slimes.

Approach:
1. For each possible set of k slimes, compute the smallest circle that encloses all of them.
2. The minimal enclosing circle for a set of points can be approximated by finding the 
   circle centered at one point and with radius equal to the maximum distance to any other point in the set.
3. However, a more efficient approach is to:
   - Sort distances from one fixed point (e.g., leftmost lowest point)
   - Use sliding window to find the minimal range that covers k points
   - The radius is then the distance of the farthest point in the window

Algorithm:
- Compute distances from a reference point (minimum x, and minimum y if tie)
- Sort all distances
- Sliding window over sorted distances: find the smallest interval such that it contains at least k points.
- Resulting radius = max_distance - min_distance in the best window

Time Complexity: O(n log n) due to sorting; sliding window is O(n)
Space Complexity: O(n) for storing points and distances
"""

pi = 3.141592653589793
n, k = map(int, input().split())
pts = []
for _ in range(n):
    xi, yi = map(int, input().split())
    pts.append((xi, yi))

# Find the leftmost and bottom-most point as reference for distance calculation
x0, y0 = min(pts)

# Calculate distances from the reference point to all points
x = []
for xi, yi in pts:
    x.append(((x0 - xi) ** 2 + (y0 - yi) ** 2) ** 0.5)

# Sort distances
x.sort()

# Sliding window: find minimal interval that covers k points
poss = []
for i in range(n - k + 1):
    # The minimum radius needed is the difference between farthest and closest point in window
    poss.append(x[i + k - 1] - x[i])

# The minimal such radius is the answer
z = min(poss)

# Output area of circle with radius z/2 (since we want to minimize area)
print(pi * z * z / 4)


# https://github.com/VaHiX/codeForces/