# Problem: CF 2111 A - Energy Crystals
# https://codeforces.com/contest/2111/problem/A

# ==============================================================================
# Problem: Energy Crystals
# Algorithm/Technique: Mathematical Analysis, Binary Representation
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
#
# The problem involves charging three energy crystals to a target level x.
# The constraint is that after each action, for any two crystals i and j:
#   a[i] >= floor(a[j]/2)
# This means the energy levels must be such that no crystal has less than half
# the energy of another (rounded down).
#
# Key Insight:
# The optimal way to charge all crystals is through a sequence where we build up
# the energy in a balanced fashion. The minimum number of operations can be derived
# using bit manipulation and binary representation.
#
# For x > 0, the solution uses:
# len(bin(x)) * 2 - 3
# This expression arises from analyzing how many steps are needed to reach balance
# through optimal charging strategies in a binary tree-like structure.
# ==============================================================================

for x in [*open(0)][1:]:  # Read input lines starting from second line (skip t)
    print(len(bin(int(x))) * 2 - 3)  # Compute and output the result using bit length


# https://github.com/VaHiX/codeForces/