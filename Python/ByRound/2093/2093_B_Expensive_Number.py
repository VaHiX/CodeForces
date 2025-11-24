# Problem: CF 2093 B - Expensive Number
# https://codeforces.com/contest/2093/problem/B

# B. Expensive Number
# Problem Description:
# Given a positive integer n, we can remove any number of digits (including none) such that 
# the remaining number is strictly greater than zero and has at least one digit.
# The cost of a number is defined as the number divided by the sum of its digits.
# Goal: Find the minimum number of digits to remove so that the resulting number has minimum possible cost.
#
# Approach:
# - For any number, if it contains zeros, removing all non-leading zeros will reduce the digit sum,
#   but we must ensure the resulting number does not become zero.
# - The key insight is that to minimize cost (n / digit_sum), we should:
#   1. Minimize the digit sum (i.e., remove as many non-leading zeros as possible).
#   2. Ensure the result is not zero.
# - Special handling for numbers with no zeros: remove all but one digit, which will give us cost = n / 1 = n.
# - For numbers with zeros:
#   - If number is just "0", return 0.
#   - Otherwise, if it includes zeros:
#      * Remove as many internal zeros as possible while keeping the leading non-zero digit so that 
#        we don't get a zero result.
#
# Time Complexity: O(n) where n is the length of string representation of number (as we process each character)
# Space Complexity: O(1) - only using constant extra space apart from input processing

for s in [*open(0)][1:]:
    # len(s) - s.strip().rstrip("0").count("0") - 2
    # s.strip() removes leading zeros
    # .rstrip("0") removes trailing zeros after that
    # .count("0") counts remaining zeros in the middle (these can be removed to reduce digit sum)
    # Subtracted by 2 because when we have a number like "1000", 
    # the minimum cost would come from removing all inner zeros, 
    # leaving at least one non-zero digit and one zero,
    # but the original logic assumes that we remove the zeros
    print(len(s) - s.strip().rstrip("0").count("0") - 2)


# https://github.com/VaHiX/codeForces/