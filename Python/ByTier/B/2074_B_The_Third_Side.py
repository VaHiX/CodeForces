# Problem: CF 2074 B - The Third Side
# https://codeforces.com/contest/2074/problem/B

# B. The Third Side
# Purpose: Given a sequence of positive integers, repeatedly combine two elements into a third
#          such that they form a non-degenerate triangle. The goal is to maximize the final element.
# Algorithm: Greedy approach using sorting and summation.
#            Sort the array to process smaller numbers first, allowing larger values to be built up.
#            Each step adds all previous elements minus one (for triangle inequality).
# Time Complexity: O(n log n) due to sorting; operations are linear after sorting.
# Space Complexity: O(1) if we ignore input/output overhead, since only a few variables are used.

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip test case count and odd lines)
    print(sum(map(int, a := s.split())) - len(a) + 1)  # Calculate maximum last element efficiently


# https://github.com/VaHiX/codeForces/