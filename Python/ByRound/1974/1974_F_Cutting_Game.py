# Problem: CF 1974 F - Cutting Game
# https://codeforces.com/contest/1974/problem/F

"""
Code Purpose:
This code solves the "Cutting Game" problem where Alice and Bob play a game on a grid with chips.
Players take turns cutting rows or columns from the grid and earn points for chips in cut regions.
The solution uses binary search to efficiently determine which player earns points for each chip.

Algorithms/Techniques:
- Binary search to find when a chip is covered by a cut region
- Simulation of grid cuts with coordinate tracking
- Efficient point counting using parity of cut indices

Time Complexity: O(n * m * log(m))
Space Complexity: O(m)

Where n is the number of chips and m is the number of moves.
"""

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    a, b, n, m = map(int, input().split())
    # u, d, l, r represent the current boundaries of the grid
    u, d, l, r = 1, a, 1, b
    s = []  # Stores chip coordinates
    for i in range(n):
        x, y = map(int, input().split())
        s.append((x, y))
    z = []  # Stores grid boundaries after each move
    for i in range(m):
        c, k = input().strip().split()
        k = int(k)
        if c == "U":
            u += k  # Move upper boundary down
        elif c == "D":
            d -= k  # Move lower boundary up
        elif c == "L":
            l += k  # Move left boundary right
        else:
            r -= k  # Move right boundary left
        z.append((u, d, l, r))
    alice = bob = 0
    for i in range(n):
        l, r = 0, m - 1  # Binary search bounds
        while l <= r:
            mid = (l + r) // 2
            # Check if chip at s[i] is inside grid at z[mid]
            if z[mid][0] <= s[i][0] <= z[mid][1] and z[mid][2] <= s[i][1] <= z[mid][3]:
                l = mid + 1  # Chip is still in grid, continue searching
            else:
                r = mid - 1  # Chip is no longer in grid, search earlier moves
        if l != m:  # Chip was in grid at some point
            if l & 1:  # Odd-numbered move (Bob's turn)
                bob += 1
            else:  # Even-numbered move (Alice's turn)
                alice += 1
    print(alice, bob)


# https://github.com/VaHiX/CodeForces/