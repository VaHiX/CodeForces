# Problem: CF 883 M - Quadcopter Competition
# https://codeforces.com/contest/883/problem/M

"""
Code purpose: 
    This code calculates the minimal path length for a quadcopter to go around a flag and return to its starting point.
    The quadcopter moves on a grid and can only move in four directions (up, down, left, right) by one unit per step.
    
    The problem is about finding the shortest closed path that strictly contains the flag point (x2, y2) inside the cycle.
    We are given the starting point (x1, y1) and the flag point (x2, y2).
    
    The key insight is to compute the Manhattan distance between the start and flag points, then determine
    how to construct the minimal cycle based on whether the flag is aligned vertically or horizontally with the start.
    
Algorithms/Techniques:
    - Manhattan Distance Calculation
    - Special Case Handling: When start and flag are aligned (same x or same y coordinates)
    
Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using a few variables
"""

a, b = map(int, input().split())  # Read starting point coordinates
c, d = map(int, input().split())  # Read flag coordinates

# Check if the start and flag are aligned (same x or same y)
if a == c or b == d:
    # If aligned, the minimal path adds 6 extra steps to go around the flag
    print(2 * abs(a - c) + 2 * abs(b - d) + 6)
else:
    # If not aligned, the minimal path adds 4 extra steps
    print(2 * abs(a - c) + 2 * abs(b - d) + 4)


# https://github.com/VaHiX/CodeForces/