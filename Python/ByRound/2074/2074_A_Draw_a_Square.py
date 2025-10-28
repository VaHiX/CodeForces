# Problem: CF 2074 A - Draw a Square
# https://codeforces.com/contest/2074/problem/A

# ==============================================================================
# Problem: Determine if four given points can form a square.
# Algorithm/Technique: Geometric verification using distance calculation.
#
# Time Complexity: O(1) per test case (constant time due to fixed number of points)
# Space Complexity: O(1) (only using a constant amount of extra space)
# ==============================================================================

t = int(input())  # Read number of test cases
for _ in range(t):  # Iterate through each test case
    l, r, d, u = map(int, input().split())  # Read the four parameters
    
    # Check if the points form a square:
    # For a square, the distances from origin to each point must be equal,
    # and the points should be arranged such that they create a square.
    # The condition l == r == d == u ensures that all sides are equal
    # when forming a square centered at origin with axes-aligned edges.
    if l == r == d == u:
        print("Yes")  # Points can form a square
    else:
        print("No")   # Points cannot form a square


# https://github.com/VaHiX/codeForces/