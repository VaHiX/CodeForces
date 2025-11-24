# Problem: CF 1971 F - Circle Perimeter
# https://codeforces.com/contest/1971/problem/F

"""
Algorithm: 
    - This problem asks for counting the number of lattice points (integer coordinate points) 
      that lie in the annular region between two circles of radius r and r+1 centered at origin.
    - The approach uses a two-pointer technique on the circle equation x^2 + y^2 = r^2.
    - We iterate through possible x values and compute corresponding y values using the constraint 
      that the point lies within the annulus (r <= d < r+1).
    - To avoid duplicate counting, we only consider the first quadrant and multiply the result by 4.
    
Time Complexity: O(r)
Space Complexity: O(1)

Techniques used: Two-pointer approach on circle equation.
"""

for _ in range(int(input())):
    n = int(input())

    ans = 0
    x, y = 1, n  # Start with x=1, y=n (first point on the boundary)
    while y > 0:
        # If the point (x,y) is too far (outside r+1 circle), decrease both x and y
        if (x**2 + y**2) >= (n + 1) ** 2:
            x, y = x - 1, y - 1
        # If the point (x,y) is too close (inside r circle), increase x
        elif (x**2 + y**2) < n**2:
            x += 1
        # If point is in valid range, increment count and move x forward
        elif x > 0:
            ans += 1
            x += 1
    # Multiply by 4 for symmetrical quadrants and add 4 for the axes points
    print(ans * 4 + 4)


# https://github.com/VaHiX/CodeForces/