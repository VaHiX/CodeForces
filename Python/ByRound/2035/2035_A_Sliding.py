# Problem: CF 2035 A - Sliding
# https://codeforces.com/contest/2035/problem/A

# **********************************************************************
# Problem: Sum of Manhattan Distances After Removal
# Algorithm/Technique: Mathematical Observation, Sliding Window
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# **********************************************************************

for s in [*open(0)][1:]:
    n, m, r, c = map(int, s.split())
    # Calculate the sum of Manhattan distances for all people who move
    # After removing person at (r,c), all people numbered > (r-1)*m + c shift left
    # The formula computes the total Manhattan distance efficiently without simulation
    print(m - c + (2 * m - 1) * (n - r))


# https://github.com/VaHiX/codeForces/