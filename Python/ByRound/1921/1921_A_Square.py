# Problem: CF 1921 A - Square
# https://codeforces.com/contest/1921/problem/A

"""
Code Purpose:
This code determines the area of a square given four corner coordinates. The square has sides parallel to the coordinate axes.
Algorithm:
1. For each test case, read four points representing the corners of a square.
2. Identify the side length by finding the difference between x-coordinates (or y-coordinates) of two adjacent corners.
3. Square this difference to get the area.
Time Complexity: O(1) per test case, as there are always exactly 4 points and constant operations.
Space Complexity: O(1), as only a constant amount of extra space is used.
"""

for _ in range(int(input())):  # Read number of test cases
    ans = 0  # Initialize variable to store side length
    done = -1  # Flag to indicate if we've found the side length
    for i in range(4):  # Process each of the four corners
        a, b = map(int, input().split())  # Read x and y coordinates
        if done == -1:  # If we haven't calculated the side length yet
            if i == 0:  # For the first point, store its x-coordinate
                ans = a
            elif ans != a:  # If x-coordinate differs from the first point
                ans -= a  # Calculate the difference (side length)
                done = 1  # Mark that we've found the side length
    print(ans * ans)  # Output the area (side length squared)


# https://github.com/VaHiX/CodeForces/