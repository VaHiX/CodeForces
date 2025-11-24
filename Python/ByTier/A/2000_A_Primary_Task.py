# Problem: CF 2000 A - Primary Task
# https://codeforces.com/contest/2000/problem/A

# ==============================================================================
# Problem: Determine if a given integer could have been the important integer n = 10^x (x >= 2)
#          that Dmitry wrote without the '^' symbol.
#
# Algorithm:
#   - For each input number, check if it can be interpreted as "10" followed by digits
#     such that the whole string represents a number of the form 10^x where x >= 2.
#   - This is done by checking specific conditions on prefix and suffix:
#     - The first 2 characters must not start with "10" (i.e., s[:2] > "10")
#     - Or the substring from index 2 onwards must be less than "1 "
#       (effectively checking if it's a string that would form a valid exponent)
#   - This is an optimized trick to check if the number could have been formed by
#     concatenating "10" + exponents like "5" for 10^5.
#
# Time Complexity: O(t), where t is the number of integers (single pass through input)
# Space Complexity: O(1), only using constant extra space regardless of input size
# ==============================================================================

for s in [*open(0)][1:]:  # Read all lines and skip first (t) line, iterate each integer string
    print("YNEOS"[s[:2] > "10" or "1 " > s[2:] :: 2])  # Check conditions and print YES/NO using slice trick


# https://github.com/VaHiX/codeForces/