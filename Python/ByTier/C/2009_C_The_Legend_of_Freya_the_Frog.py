# Problem: CF 2009 C - The Legend of Freya the Frog
# https://codeforces.com/contest/2009/problem/C

# C. The Legend of Freya the Frog
# Time complexity: O(1) per test case
# Space complexity: O(1)
# 
# Algorithm:
# Freya alternates between moving in x and y directions.
# For each direction, we compute how many moves are needed to reach the required distance,
# considering that in one move she can go up to k units.
# The key insight is that for each coordinate, we need to cover it in alternating steps,
# where the number of such steps depends on how many full k-steps plus one additional step (if remainder exists)
# are needed.
#
# For example:
# - In x-direction: (x // k) + (1 if x % k > 0 else 0) moves are needed to reach x
# - Same applies for y-direction.
# But since she alternates, we have two interleaved sequences of moves.
# We combine them into a single formula:
# The minimum number of steps is computed by considering how many full steps in both directions,
# and then computing the final result using min operations and sign manipulation.

for s in [*open(0)][1:]:
    x, y, k = map(int, s.split())
    # Compute total steps using mathematical simplification:
    # The expression computes the number of moves needed for each axis
    # taking into account alternating moves and maximum jump distance k.
    print(-min(-x // k * 2 + 1, -y // k * 2))


# https://github.com/VaHiX/codeForces/