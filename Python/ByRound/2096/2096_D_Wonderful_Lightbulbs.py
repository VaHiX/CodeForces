# Problem: CF 2096 D - Wonderful Lightbulbs
# https://codeforces.com/contest/2096/problem/D

"""
D. Wonderful Lightbulbs

Problem Description:
We are given a configuration of lightbulbs that are ON in an infinite grid.
Each operation switches the state of four adjacent bulbs in a specific pattern:
(x, y), (x, y+1), (x+1, y-1), (x+1, y)
This operation can be thought of as a XOR operation on the bulb states.
We need to find one possible initial position of the treasure (a bulb that was originally turned ON).

Key Insight:
Since operations are reversible and each operation toggles 4 bulbs, we can think of this in terms
of XOR properties. The final configuration can be represented as a combination of these operations.

Approach:
Use XOR operations on x and x+y coordinates to compute the possible initial position.
The key idea is that for each bulb at (x_i, y_i), we track the XOR of x and the XOR of (x + y),
which leads us to determine a valid (s, t) where s ^= x and c ^= x + y.
Eventually, the result gives one valid solution (s, c - s).

Time Complexity: O(n)
Space Complexity: O(1)

This problem is about finding a consistent initial state by exploiting properties of XOR operations
on patterns of toggling bulbs in a grid.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    s = 0   # XOR of all x coordinates
    c = 0   # XOR of (x + y) for all coordinates
    for _ in range(n):
        x, y = map(int, input().split())
        s ^= x           # Accumulate XOR of x values
        c ^= x + y       # Accumulate XOR of (x + y) values
    print(s, c - s)      # Output the computed candidate position


# https://github.com/VaHiX/codeForces/