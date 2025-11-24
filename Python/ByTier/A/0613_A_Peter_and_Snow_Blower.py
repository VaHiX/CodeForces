# Problem: CF 613 A - Peter and Snow Blower
# https://codeforces.com/contest/613/problem/A

"""
Problem: Peter and Snow Blower

The snow blower is modeled as a polygon. When tied to a point P and switched on, it rotates around P,
clearing area in a circular pattern. The task is to compute the area of the region cleared from snow.

Approach:
- The snow blower (polygon) rotates around point P.
- The minimum and maximum distances from P to any point on the polygon determine the inner and outer radii.
- The difference in areas of two circles (with these radii) gives the cleared area.

Key Steps:
1. Compute the squared distance from P to each vertex of the polygon.
2. For each edge of the polygon, compute the squared distance from P to the closest point on the edge.
3. Find the maximum of vertex distances and minimum of edge distances.
4. Compute the area as π * (maxr^2 - minr^2).

Time Complexity: O(n) where n is the number of vertices
Space Complexity: O(n) for storing the vertices

Algorithms/Techniques:
- Geometry: Distance from point to line segment
- Polygon processing: Loop through vertices and edges
"""

import math
import sys


def dist2(x1, y1, x2, y2):
    # Compute squared distance between two points
    return (x1 - x2) ** 2 + (y1 - y2) ** 2


def find_dist(x1, y1, x2, y2, X, Y):
    # Find squared distance from point (X,Y) to the line segment from (x1,y1) to (x2,y2)
    if x2 == x1:
        # Vertical line
        if min(y1, y2) <= Y <= max(y1, y2):
            # Point is vertically aligned with the segment
            return (x1 - X) ** 2
        else:
            # Point is not vertically aligned, return min distance to endpoints
            return min(dist2(x1, y1, X, Y), dist2(x2, y2, X, Y))
    
    # Calculate the line equation y = a*x + b
    a = (y2 - y1) / (x2 - x1)
    b = y1 - a * x1
    
    # Find x-coordinate of the closest point on the line to (X,Y)
    x = (X + a * (Y - b)) / (1 + a * a)
    
    if min(x1, x2) <= x <= max(x1, x2):
        # Closest point lies on the segment
        return dist2(x, a * x + b, X, Y)
    else:
        # Closest point is one of the endpoints
        return min(dist2(x1, y1, X, Y), dist2(x2, y2, X, Y))


def main():
    # Read number of vertices and coordinates of point P
    N, X, Y = map(int, sys.stdin.readline().split())
    
    # Initialize min and max radius trackers
    maxr = 0
    minr = 10**15
    
    # Read polygon vertices
    pts = [tuple(map(int, sys.stdin.readline().split())) for _ in range(N)]
    # Append first vertex to close the loop
    pts.append(pts[0])
    
    # Process each edge of the polygon
    for i in range(0, len(pts) - 1):
        x, y = pts[i]
        # Compute squared distance from P to current vertex
        r = dist2(x, y, X, Y)
        if r > maxr:
            maxr = r
        # Compute squared distance from P to the closest point on current edge
        r = find_dist(x, y, pts[i + 1][0], pts[i + 1][1], X, Y)
        if r < minr:
            minr = r

    # Output area as difference of two circle areas
    print("%.10f" % (math.pi * (maxr - minr)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/