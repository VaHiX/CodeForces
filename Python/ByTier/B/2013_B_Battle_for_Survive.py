# Problem: CF 2013 B - Battle for Survive
# https://codeforces.com/contest/2013/problem/B

# ******************************************************************************
# Problem: B. Battle for Survive
# Purpose: Maximize the final rating of the last remaining fighter by optimally
#          choosing which fighters battle each other.
#
# Algorithm: Greedy approach.
#            The key insight is that we can simulate the process by always
#            eliminating the smallest-rated fighter and adding its rating to
#            the largest-rated remaining fighter. This ensures maximum final rating.
#
# Time Complexity: O(n log n) due to sorting
# Space Complexity: O(n) for input storage and processing
# ******************************************************************************

for s in [*open(0)][2::2]:  # Iterate through test cases, skipping line numbers
    a = (*map(int, s.split()),)  # Parse the fighter ratings into a tuple
    print(sum(a) - a[-2] * 2)  # Compute maximum possible final rating


# https://github.com/VaHiX/codeForces/