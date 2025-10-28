# Problem: CF 2019 A - Max Plus Size
# https://codeforces.com/contest/2019/problem/A

# ==================================================================
# Problem: Max Plus Size
# Algorithm: Dynamic Programming / Greedy
# Time Complexity: O(n) per test case
# Space Complexity: O(1) extra space (excluding input)
#
# Given an array of positive integers, we can color some elements red 
# such that no two adjacent elements are both red. The score is the 
# maximum red element plus the number of red elements.
# We aim to maximize this score.
#
# Approach:
# For each possible position to start a sequence of non-adjacent red elements,
# calculate the total score (max element + count), then take the maximum.
# The key insight is to process all valid sequences efficiently using 
# a greedy-like strategy over the array values.
# ==================================================================

for s in [*open(0)][2::2]:  # Read input lines skipping every other (test cases and lengths)
    a = s.split()  # Convert current line to list of strings (the array elements)
    print(max(i // 2 + (len(a) - i + 1) // 2 + int(x) for i, x in enumerate(a)))  # Evaluate all possible choices


# https://github.com/VaHiX/codeForces/