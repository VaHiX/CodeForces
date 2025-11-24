# Problem: CF 2101 A - Mex in the Grid
# https://codeforces.com/contest/2101/problem/A

"""
Code Purpose:
    This function generates a "magical spiral" grid of size n x n, starting from the center
    and spiraling outward in a clockwise pattern. The spiral fills numbers from 0 to n*n-1.

Algorithms/Techniques:
    - Spiral traversal with direction changes
    - Grid filling based on step patterns

Time Complexity: O(n^2)
Space Complexity: O(n^2)

The function initializes a grid, places the starting value (0) in the center,
and then follows a spiral pattern to fill all cells with sequential integers.
"""

def magical_spiral(n):
    # Initialize the grid with -1 (unfilled cells)
    arr = [[-1] * n for _ in range(n)]
    
    # Determine the starting position based on whether n is even or odd
    if n % 2 == 0:
        x, y = n // 2 - 1, n // 2 - 1  # For even n, start at center-left-bottom
    else:
        x, y = n // 2, n // 2  # For odd n, start at exact center
    
    # Place the starting value (0) at the determined position
    arr[x][y] = 0
    
    # Set initial parameters for spiral traversal
    value = step = 1  # 'value' is the number to place next, 'step' controls how many steps to take in a direction
    dir = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Right, Down, Left, Up
    
    # Continue until all cells are filled (n * n total cells)
    while value < n * n:
        for d in range(4):  # Traverse each of the four directions
            steps = step  # Take 'step' number of steps in current direction
            # Increment step every other turn to control spiral width
            step += d % 2
            
            dx, dy = dir[d]  # Get the directional offset
            
            for _ in range(steps):  # Move step times in current direction
                x += dx
                y += dy
                
                # Check if move is valid and cell is unfilled
                if 0 <= x < n and 0 <= y < n and arr[x][y] == -1:
                    arr[x][y] = value  # Place the next number
                    value += 1  # Increment the number to place
                    
                # Early exit if all cells are filled
                if value >= n * n:
                    break
            
            # Early exit if all cells are filled
            if value >= n * n:
                break
    
    # Print the resulting grid
    for row in arr:
        print(" ".join(str(num) for num in row))
    print()


t = int(input())
for _ in range(t):
    n = int(input())
    magical_spiral(n)


# https://github.com/VaHiX/codeForces/