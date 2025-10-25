# Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
# https://codeforces.com/contest/2127/problem/B

"""
B. Hamiiid, Haaamid... Hamid?
Algorithm: Two-pointer technique with greedy optimization.
Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(1), only using a few variables for computation.

This problem models a game between Mani and Hamid on a 1D grid. 
Hamid wants to minimize escape days; Mani wants to maximize them.
Both play optimally. On each day:
- Mani places a wall in an empty cell (not where Hamid is).
- Hamid chooses direction and either escapes or moves towards the nearest wall in that direction, destroying it.

The solution finds the minimum number of steps needed for Hamid to escape, given optimal play from both players.
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
    jl, jr = x, x  # Pointers to find closest walls on left and right
    
    # Move left while we have empty cells
    while jl >= 0 and s[jl] == ".":
        jl -= 1
    # Move right while we have empty cells
    while jr < n and s[jr] == ".":
        jr += 1
    
    # Calculate best escape path from left side:
    # Hamid can go left if there exists space to the left (or is at start)
    ansl = min(x + 1, 1 + n - jr)  # dist to left wall or edge
    # From right side:
    ansr = min(n - x, jl + 2)      # dist to right wall or edge

    print(max(ansl, ansr))


# https://github.com/VaHiX/CodeForces/