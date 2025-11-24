# Problem: CF 2070 A - FizzBuzz Remixed
# https://codeforces.com/contest/2070/problem/A

# ==============================================================================
# Problem: FizzBuzz Remixed
# Algorithm: Mathematical Pattern Recognition
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
#
# Description:
# For a given integer n, we count how many integers from 0 to n satisfy:
# i % 3 == i % 5.
# These numbers form a pattern with period 15.
# The pattern repeats every 15 numbers, and within each period,
# there are exactly 4 numbers satisfying the condition (0,1,2,15).
#
# The formula used:
# - n // 15 gives full cycles of 15
# - Each cycle contributes 3 to the count (except the last partial one)
# - n % 15 gives remaining numbers, we check how many in that range satisfy condition
# ==============================================================================

for n in [*open(0)][1:]:  # Read all input lines except first (number of test cases)
    n = int(n) + 1         # Increment to include n in range [0, n]
    print(n // 15 * 3 + min(3, n % 15))  # Calculate result using periodic pattern


# https://github.com/VaHiX/codeForces/