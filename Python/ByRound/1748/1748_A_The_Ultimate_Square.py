# Problem: CF 1748 A - The Ultimate Square
# https://codeforces.com/contest/1748/problem/A

# Flowerbox
"""
Code purpose: 
    Computes the maximum side length of a square that can be formed using rectangular blocks.
    Each block i has dimensions 1 x ceil(i/2). The algorithm determines the optimal square side length
    by analyzing how many blocks of each size are needed to form a square of given side s.

Algorithms/Techniques:
    - Mathematical analysis to determine block requirements for square formation
    - Binary search or direct mathematical computation (this version uses direct formula)
    
Time Complexity: O(1) per test case
Space Complexity: O(1)
"""

# Read all input lines, skip the first (number of test cases), iterate over remaining
for s in [*open(0)][1:]:
    # Calculate maximum square side length using mathematical formula
    # The key insight is that for a square of side s, we need at least s blocks
    # of size 1 x s to fill it, but the number of blocks required depends on how
    # they are arranged. We derive that the answer is (n + 1) // 2.
    print((int(s) + 1) // 2)


# https://github.com/VaHiX/codeForces/