# Problem: CF 1807 F - Bouncy Ball
# https://codeforces.com/contest/1807/problem/F

"""
Algorithm: Simulation with Bouncing
Approach:
- Simulate the ball movement in the grid according to the given direction.
- When the ball hits a wall, flip the corresponding direction component (dx or dy).
- Count the number of bounces until the ball reaches the target cell or exceeds a safe iteration limit.
- If the ball never reaches the target, return -1.

Time Complexity: O(n * m) per test case in the worst case due to simulation
Space Complexity: O(1) - only using a few variables for tracking state

Techniques:
- Direction handling using dx and dy components
- Wall collision detection and direction flipping
- Early termination when target is reached
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    S = input().split()
    n, m, frmx, frmy, tox, toy = map(int, S[:-1])  # Read grid dimensions and start/target positions
    s = S[-1]  # Starting direction
    
    # Initialize dx and dy based on direction
    if "D" in s:
        dx = 1  # Moving downward
    else:
        dx = -1  # Moving upward
    
    if "R" in s:
        dy = 1  # Moving rightward
    else:
        dy = -1  # Moving leftward

    cnt = 0  # Counter for steps taken
    ans = 0  # Counter for number of bounces
    nowx, nowy = frmx, frmy  # Current position of the ball
    
    # Simulate until we either reach the target or exceed safe iteration limit
    while cnt < 10 * n * m:
        cnt += 1
        # Check if current position matches the target
        if nowx == tox and nowy == toy:
            print(ans)
            return
        
        flag = 0  # Flag to indicate if a bounce occurred in this step
        
        # Check collision with top wall
        if nowx == 1 and dx == -1:
            dx = 1  # Flip vertical direction
            flag = 1
        
        # Check collision with bottom wall
        if nowx == n and dx == 1:
            dx = -1  # Flip vertical direction
            flag = 1
        
        # Check collision with left wall
        if nowy == 1 and dy == -1:
            dy = 1  # Flip horizontal direction
            flag = 1
        
        # Check collision with right wall
        if nowy == m and dy == 1:
            dy = -1  # Flip horizontal direction
            flag = 1
            
        ans += flag  # Increment bounce count if a bounce happened
        nowx += dx  # Move ball in x direction
        nowy += dy  # Move ball in y direction

    print(-1)  # Ball never reached target
    return


testcase = int(input())
for _ in range(testcase):
    solve()


# https://github.com/VaHiX/CodeForces/