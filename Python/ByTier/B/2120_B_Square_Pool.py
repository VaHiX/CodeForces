# Problem: CF 2120 B - Square Pool
# https://codeforces.com/contest/2120/problem/B

"""
B. Square Pool

Purpose:
This code determines how many balls are potted in a square pool game based on their initial positions and directions.
Each ball moves with speed 10^100 units/sec at 45 degrees to the axes, bouncing off walls elastically.
A ball is considered potted if it reaches any of the four corners (pockets) of the square table.

Algorithms/Techniques:
- Simulation of ball movement through reflections
- Mathematical analysis: a ball reaches a pocket if its trajectory aligns with a pocket in terms of direction and position
- Key insight: the trajectory can be simplified by considering reflections; a ball is potted if either:
  1. Its initial position (x+y) equals target pocket sum, and its movement vector is perpendicular to the pocket's axis
  2. Its initial position (x==y), and direction vector matches orientation

Time Complexity: O(n), where n is number of balls (single loop over all balls)
Space Complexity: O(1), only using constant extra space for variables

Input Format:
- First line has t (number of test cases)
- For each test case:
  - First line: n s (number of balls, side length of table)
  - Next n lines: dx dy x y (directions and initial coordinates)

Output:
Number of balls potted in each test case.
"""

for _ in range(int(input())):
    n, s = map(int, input().split())  # Read number of balls and table size
    ans = 0  # Initialize counter for potted balls
    for _ in range(n):
        dx, dy, x, y = map(int, input().split())  # Read ball's direction and position
        
        # Check condition 1: if moving towards a corner (sum of coordinates)  
        # and velocity is along the axis normal to that direction
        if (x + y == s and dx + dy == 0) or (x == y and dx == dy):
            ans += 1  # Increment counter if ball will reach a pocket
            
    print(ans)  # Print result for current test case


# https://github.com/VaHiX/codeForces/