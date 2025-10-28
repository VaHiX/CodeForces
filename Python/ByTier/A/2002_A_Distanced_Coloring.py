# Problem: CF 2002 A - Distanced Coloring
# https://codeforces.com/contest/2002/problem/A

# """
# Problem: Grid Coloring with Minimum Colors
# 
# Algorithm/Technique: Distanced Coloring
# 
# Approach:
# The constraint max(|x1−x2|, |y1−y2|) ≥ k means that two cells with the same color 
# must be at least k units apart in either row or column direction.
# 
# We can think of this as placing "coloring blocks" of size k×k, and each block
# requires a different color. The minimal number of colors needed is determined by
# how many such non-overlapping k×k blocks fit into the n×m grid.
# 
# Time Complexity: O(1) per test case - constant time operations
# Space Complexity: O(1) - only using a constant amount of extra space
# """
for s in [*open(0)][1:]:
    n, m, k = map(int, s.split())
    # Calculate the minimum number of colors needed by determining how many 
    # non-overlapping k×k blocks fit in the grid in each dimension, then multiply
    print(min(n, k) * min(m, k))


# https://github.com/VaHiX/codeForces/