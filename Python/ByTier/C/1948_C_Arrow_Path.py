# Problem: CF 1948 C - Arrow Path
# https://codeforces.com/contest/1948/problem/C

"""
Algorithm: Arrow Path
Approach: 
    - The robot starts at (1,1) and must reach (2,n).
    - At each step, the robot moves in a direction based on the arrow in its current cell, 
      and then moves according to the arrow in that new cell.
    - We simulate possible paths by tracking valid transitions between cells.
    - Key idea: Check if it's possible to traverse from row 1 to row 2 at some column,
      ensuring the movement path is feasible and follows the arrows.

Time Complexity: O(n) where n is the number of columns.
Space Complexity: O(n) for storing candidate movement directions.
"""

import sys

input = sys.stdin


def solve(N, arr):
    if N == 2:
        return "YES\n"
    candits = []
    # Build a list of candidate moves by alternating between rows
    for i in range(N - 1):
        if i % 2 == 0:
            candits.append(arr[1][i])  # Take from row 2
        else:
            candits.append(arr[0][i])  # Take from row 1
    # Check for invalid sequences of moves
    for a, b in zip(candits[:-1], candits[1:]):
        if a == "<" and b == "<":
            return "NO\n"
    # If the last move points left, it's impossible to proceed further
    if candits[-1] == "<":
        return "NO\n"
    return "YES\n"


T = int(input.readline().strip())
for _ in range(T):
    N = int(input.readline().strip())
    arr = [input.readline().strip() for _ in range(2)]
    print(solve(N, arr))


# https://github.com/VaHiX/CodeForces/