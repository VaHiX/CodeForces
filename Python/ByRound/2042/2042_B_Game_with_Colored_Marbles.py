# Problem: CF 2042 B - Game with Colored Marbles
# https://codeforces.com/contest/2042/problem/B

# ******************************************************************************
# Problem: B. Game with Colored Marbles
# Algorithm: Game Theory + Greedy Analysis
# Time Complexity: O(n) per test case, where n is the number of marbles
# Space Complexity: O(n) for storing color counts and set operations
# 
# Approach:
# - For each test case:
#   1. Count occurrences of each color.
#   2. Determine how many colors have exactly one marble (Alice gets 1 point for taking at least one).
#   3. Determine how many colors have more than one marble (Alice might get points for taking all, but it's not always optimal).
#   4. The key insight is:
#      - If a color appears once: Alice gets 1 point if she takes the only marble.
#      - If a color appears more than once: She gets 1 point if she takes all marbles of that color.
#   5. Since Alice goes first and both play optimally, we simulate the optimal outcome:
#      - All colors with count 1 contribute to her points (she can take one).
#      - For each color appearing more than once, Alice can take all if she goes first in a round.
#      - The final score is based on how many distinct colors Alice ends up covering,
#        plus bonuses for full coverage of some colors.
#
# Note:
# This implementation simplifies the problem by focusing on counting.
# It assumes that optimal play results in maximizing her advantage from unique counts.
# ******************************************************************************

for s in [*open(0)][2::2]:  # Process odd lines (test case data), 0-indexed
    a = s.split()  # Get list of colors for current test case
    a = (*map(a.count, {*a}),)  # Count occurrences of each unique color and form tuple
    print(len(a) + a.count(1) % 2)  # Output computed score


# https://github.com/VaHiX/codeForces/