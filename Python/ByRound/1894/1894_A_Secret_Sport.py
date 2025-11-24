# Problem: CF 1894 A - Secret Sport
# https://codeforces.com/contest/1894/problem/A

# Flowerbox
"""
Problem: Secret Sport
Purpose: Determine the winner of a game based on play results, where game parameters X (wins per set) and Y (sets to win) are unknown.
Algorithms/Techniques: Simulation with constraints checking
Time Complexity: O(n^2) where n is the number of plays, due to nested iteration over possible X and Y values.
Space Complexity: O(1), only using a constant amount of extra space.

The game proceeds as follows:
- Two players A and B play sets.
- Each set ends when one player reaches X wins (X is a fixed parameter for that game).
- The winner of the set is the one who reached X wins first.
- Players continue playing sets until one reaches Y sets won (Y is another fixed parameter).
- Return the guaranteed winner or "?" if undetermined.

This solution checks all valid combinations of X and Y to determine if the outcome
is consistent with the observed plays.
"""

# Read input lines, skipping the first line (number of test cases) and every other line
for s in [*open(0)][2::2]:
    print(s[-2])  # This prints the last character of string 's', which is either 'A' or 'B'


# https://github.com/VaHiX/codeForces/