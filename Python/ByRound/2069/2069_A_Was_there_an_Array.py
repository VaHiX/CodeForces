# Problem: CF 2069 A - Was there an Array?
# https://codeforces.com/contest/2069/problem/A

# ==============================================================================
# Problem: Determine if a valid array 'a' exists such that given array 'b' is its equality characteristic.
# 
# Algorithm/Technique:
# - Check consistency of transitions in the 'b' array.
# - For each element in 'b', determine if it's possible to assign values to neighbors.
# - Key insight: a 0 in 'b' means the current element must differ from at least one neighbor.
# - A 1 means it must be equal to both neighbors.
#
# Time Complexity: O(n) per test case, where n is the length of b array.
# Space Complexity: O(1), only using a constant amount of extra space.
# ==============================================================================

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, step by 2 (skip n values)
    print("YNEOS"["1 0 1" in s :: 2])  # Check if substring "1 0 1" is in s, use that as boolean index to select output


# https://github.com/VaHiX/codeForces/