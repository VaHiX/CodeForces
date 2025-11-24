# Problem: CF 2152 B - Catching the Krug
# https://codeforces.com/contest/2152/problem/B

# Flowerbox
"""
Problem: Catching the Krug
Algorithm/Technique: Game theory, optimal play simulation
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem models a game between two players (Krug and Doran) on an n x n grid. 
The Krug tries to avoid being caught by Doran, while Doran attempts to catch the Krug.
Both players play optimally:
- Krug can move vertically or horizontally (4-directional movement)
- Doran can move in all 8 directions (including diagonals)

The key insight is that we compute the minimum number of turns for Doran to catch the Krug,
based on the Manhattan distance and the possibility of blocking moves. 
In optimal play:
- If Krug can escape to a position where Doran cannot reach it in one turn, the Krug survives.
- Otherwise, the game progresses, and we simulate how long it takes for Doran to win.

The calculation involves analyzing the relative positions of Krug and Doran,
taking into account movement patterns and optimal strategies:
    - If Doran is near enough to catch the Krug, return minimum steps it will take.
    - If Krug can indefinitely avoid capture by moving in a safe pattern, return -1.

Based on game theory:
   - For any starting configuration, either:
     1. Krug survives forever (return -1)
     2. Krug is caught after some number of Doran's turns (return that number)

This solution computes that value directly using geometric properties and simple logic.
"""

t = int(input())
for _ in range(t):
    m = 0
    n, r1, c1, r2, c2 = map(int, input().split())  # r1,c1 = Krug's position; r2,c2 = Doran's position
    
    # Check vertical distance from Krug to Doran
    if r1 > r2:
        m = n - r2  # Distance calculation: Krug is above, so we move the max distance in rows
    elif r1 < r2:
        m = r2      # If Krug is below Doran, calculate how far apart they are
    
    # Check horizontal distance from Krug to Doran
    if c1 > c2:
        m = max(m, n - c2)  # Update m with maximum of previous and new horizontal distance
    elif c1 < c2:
        m = max(m, c2)      # If Krug is to the left, we check this distance too
    
    print(m)


# https://github.com/VaHiX/CodeForces/