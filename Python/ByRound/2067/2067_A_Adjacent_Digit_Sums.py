# Problem: CF 2067 A - Adjacent Digit Sums
# https://codeforces.com/contest/2067/problem/A

# ============================================================================
# Problem: Adjacent Digit Sums
# 
# Given two integers x and y, determine if there exists an integer n such that:
#   S(n) = x and S(n+1) = y
# where S(a) is the sum of digits of a.
#
# Algorithm:
#   - For consecutive numbers n and n+1, the digit sum changes in specific ways.
#   - If n ends with k trailing 9s, then n+1 will have a carry that reduces those 9s to 0s,
#     and the first non-9 digit increases by 1.
#   - The change in digit sums can be modeled as:
#     if last k digits are 9s: y = x - 9*k + 1
#     rearranging gives: x - y = 9*k - 1 => (x - y + 1) % 9 == 0 and (x - y + 1) / 9 >= k
#   - Also, we must check if the digit sum of n+1 can be one more than n's sum.
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# =============================================================================

for s in [*open(0)][1:]:
    x, y = map(int, s.split())
    y -= x  # Difference between sums
    print("NYoe s"[y <= 1 == y % 9 :: 2])  # Output based on conditions


# https://github.com/VaHiX/codeForces/