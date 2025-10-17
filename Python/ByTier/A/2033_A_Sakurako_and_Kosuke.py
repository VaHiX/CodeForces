# Problem: CF 2033 A - Sakurako and Kosuke
# https://codeforces.com/contest/2033/problem/A

# ==============================================================================
# Problem: Determine the winner of a game between Sakurako and Kosuke
# where they alternate moving a dot on a number line.
#
# Algorithm/Technique:
# - Simulation of game moves
# - Pattern recognition based on parity of n
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==============================================================================

for n in [*open(0)][1:]:  # Read all input lines except first (number of games)
    print("SKaoksuurkaek o"[int(n) % 2 :: 2])  # Use modular arithmetic to determine winner


# https://github.com/VaHiX/codeForces/