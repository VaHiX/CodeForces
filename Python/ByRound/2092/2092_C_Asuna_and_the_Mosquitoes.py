# Problem: CF 2092 C - Asuna and the Mosquitoes
# https://codeforces.com/contest/2092/problem/C

"""
C. Asuna and the Mosquitoes

Purpose:
This code solves a problem where Asuna wants to maximize the beauty (maximum height) of her towers by redistributing
the heights through operations that transfer 1 unit from an even tower to an odd tower, if possible.

Algorithms/Techniques:
- Greedy redistribution based on parity (even/odd).
- Counting number of odd elements.
- If there are both even and odd elements, we can move units toward making one element as large as possible.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The key insight is:
- If all numbers are even, the maximum stay unchanged.
- If some are odd, then there's a way to redistribute such that the max can be increased by at most 1 more than the sum of odds.
"""

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip n and empty lines)
    a = (*map(int, s.split()),)  # Convert string of numbers to tuple of integers
    k = sum(x % 2 for x in a)  # Count number of odd elements
    print((max(a), sum(a) - k + 1)[0 < k < len(a)])  # Print max if all even or all odd; else sum - odds + 1


# https://github.com/VaHiX/codeForces/