# Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
# https://codeforces.com/contest/2127/problem/B

"""
B. Hamiiid, Haaamid... Hamid?
Algorithms/Techniques: Two-pointer technique, greedy strategy

Time Complexity: O(n) for each test case, where n is the length of the string s
Space Complexity: O(1), as we only use a constant amount of extra space

The problem models a game between Hamid and Mani on a 1D grid. Hamid wants to escape 
as quickly as possible, while Mani tries to delay it. Both play optimally.

Key idea:
- On each day, Mani places a wall in an empty cell (not where Hamid is).
- Then Hamid moves toward the nearest wall in either direction and destroys it.
- Hamid escapes if he reaches the edge of the grid.

We analyze the problem by finding how far Hamid can go to the left or right before 
being blocked, and then determine optimal moves for both players.

Approach:
1. Use two pointers to find the range of empty cells from Hamid's position.
2. Calculate maximum number of steps Hamid can take based on nearest walls in both directions.
3. Take minimum of these two possible escape paths.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, x = map(int, input().split())
    s = input()
    x -= 1  # Convert to 0-based indexing
    if x == 0 or x == n - 1:
        print(1)
        continue
    jl, jr = x, x  # Initialize pointers at Hamid's position
    
    # Move left while we encounter empty cells ('.')
    while jl >= 0 and s[jl] == ".":
        jl -= 1
    # Move right while we encounter empty cells ('.')
    while jr < n and s[jr] == ".":
        jr += 1
    
    # Calculate how many steps Hamid can take to the left
    ansl = min(x + 1, 1 + n - jr)
    # Calculate how many steps Hamid can take to the right
    ansr = min(n - x, jl + 2)
    print(max(ansl, ansr))


# https://github.com/VaHiX/codeForces/