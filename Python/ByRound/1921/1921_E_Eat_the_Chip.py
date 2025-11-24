# Problem: CF 1921 E - Eat the Chip
# https://codeforces.com/contest/1921/problem/E

"""
Algorithm: Game Theory, Strategic Position Analysis
Techniques: 
- Analyzing parity (odd/even) of moves to determine win/loss conditions
- Using geometric constraints to determine if one player can catch the other
- Precomputing possible winning conditions based on relative positions

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a fixed amount of variables regardless of input size

This code determines the winner of a game on a grid where Alice moves down and Bob moves up,
with specific movement rules and win conditions. The solution uses mathematical analysis
to determine optimal play without needing to simulate the entire game.
"""

import sys


def solution(h, w, xa, ya, xb, yb):
    # If Alice is already at or below Bob, she cannot move towards him
    if xa >= xb:
        return "Draw"
    
    # If the distance between rows is even
    if not (xb - xa) % 2:
        t = (xb - xa) // 2  # Number of moves needed to meet
        # If Alice is to the right of Bob
        if ya > yb:
            # Check if there's an overlap in movement path that would allow Bob to win
            # If the rightmost possible column for Alice (ya + t) is beyond valid board width,
            # or if the leftmost possible column for Bob (yb - t) would go out of bounds (1),
            # then Bob cannot win, so result is drawn
            return "Draw" if yb + t < min(w, ya + t) else "Bob"
        else:
            # Same logic, but Alice moves left (ya - t) 
            return "Draw" if yb - t > max(1, ya - t) else "Bob"
    else:
        # If the distance between rows is odd
        t = (xb - xa) // 2  # Number of moves needed to meet
        # If Alice is to the left of Bob
        if ya < yb:
            # Check if Alice can win by reaching Bob's side
            # If the rightmost possible column for Alice (ya + t + 1) is beyond valid board width,
            # or if the leftmost possible column for Bob (yb - t) is out of bounds (1),
            # then result is drawn
            return "Draw" if ya + t + 1 < min(w, yb + t) else "Alice"
        else:
            # Similar logic for when Alice is to the right of Bob
            return "Draw" if ya - t - 1 > max(1, yb - t) else "Alice"


for i, line in enumerate(sys.stdin):
    if i == 0:
        continue
    line = map(int, line.strip().split())
    sys.stdout.write(solution(*line) + "\n")


# https://github.com/VaHiX/CodeForces/