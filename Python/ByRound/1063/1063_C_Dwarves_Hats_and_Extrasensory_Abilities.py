# Problem: CF 1063 C - Dwarves, Hats and Extrasensory Abilities
# https://codeforces.com/contest/1063/problem/C

"""
Task: Split n points on a 2D plane into two groups (black and white) using a line,
where no point lies on the line, and all points of one color are on the same side.

Algorithm:
- We use a binary search approach on x-coordinate to place points.
- Initially, we place a point at (r, 1) where r = 10^9.
- Based on the color of this point, we determine the color of the leftmost point.
- Then, for subsequent points, we use binary search to find a good x-coordinate,
  making sure to place each point in a way that separates the two colors.
- Finally, we output two points that define a separating line.

Time Complexity: O(n * log(max_x)) where max_x = 10^9
Space Complexity: O(1) - only a few variables used.
"""

def solv(n):
    l = 0  # left boundary for binary search
    r = int(1e9)  # right boundary for binary search
    print(r, 1)  # place first point at (r, 1)
    rc = input()  # read color of first point
    # determine color of leftmost point based on first point's color
    lc = "white" if rc == "black" else "black"
    for i in range(1, n):  # place remaining n-1 points
        m = (l + r) // 2  # calculate mid point for binary search
        print(m, 1)  # place point at (m, 1)
        mc = input()  # read color of current point
        # adjust search boundaries based on color
        if mc == lc:
            l = m  # move left boundary to mid
        else:
            r = m  # move right boundary to mid
    # output two points defining the separating line
    print(l, 0, r, 2)

n = int(input())
solv(n)


# https://github.com/VaHiX/CodeForces/