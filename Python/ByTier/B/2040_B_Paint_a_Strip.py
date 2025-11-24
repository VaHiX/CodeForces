# Problem: CF 2040 B - Paint a Strip
# https://codeforces.com/contest/2040/problem/B

# Problem: B. Paint a Strip
# Purpose: Given an array of zeros of length n, determine the minimum number of operations 
#          of type 1 (setting a zero to one) needed to make all elements equal to one.
#          Type 2 operations allow setting all elements in a segment [l,r] to 1 if 
#          sum of elements in that range is at least ceil((r-l+1)/2).
# Algorithm: The key insight is that we want to minimize the number of type 1 operations.
#            We can model this as finding the minimum number of 1s needed, such that 
#            the remaining zeros can be covered using type 2 operations optimally.
#            This problem reduces to calculating how many segments (each covering at least half 
#            of its length with 1s) we need, which is equivalent to computing ceil(log2((n + 2) / 3)) + 1.
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

from math import ceil, log2

for i in [*open(0)][1:]:
    print(ceil(log2((int(i) + 2) / 3)) + 1)


# https://github.com/VaHiX/codeForces/