# Problem: CF 2092 A - Kamilka and the Sheep
# https://codeforces.com/contest/2092/problem/A

# ============================================================================
# Problem: A. Kamilka and the Sheep
# Purpose: Find the maximum possible GCD of any two sheep's beauty levels
#          after choosing an optimal non-negative integer d to add to all sheep.
#
# Algorithm:
#   - For each test case, we compute the GCD of all pairs (a_i + d, a_j + d)
#     for different values of d.
#   - A key insight is that increasing all elements by same d does not change
#     pairwise differences. So we can focus on differences between original values,
#     and the problem reduces to choosing a d such that GCD of some pair becomes maximum.
#   - The approach: Try all possible pairs, compute their GCD, and find maximum.
#
# Time Complexity: O(n^2 * log(max(a))) where n is number of sheep
# Space Complexity: O(1) - only using constant extra space
# ============================================================================

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip t and n)
    m, *_, M = sorted(map(int, s.split()))  # Sort the numbers; m=min, M=max
    print(M - m)  # Output difference between max and min values (this is gcd after optimal d)


# https://github.com/VaHiX/codeForces/