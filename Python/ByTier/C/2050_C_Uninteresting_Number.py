# Problem: CF 2050 C - Uninteresting Number
# https://codeforces.com/contest/2050/problem/C

# C. Uninteresting Number
# 
# Purpose:
#   Determine if a number can be transformed to be divisible by 9 using allowed operations.
#   The operation allows replacing any digit with its square (only if square < 10).
#   Allowed squares: 0²=0, 1²=1, 2²=4, 3²=9. So digits 0,1,2,3 are valid for transformation.
#
# Algorithm:
#   - Use modular arithmetic properties of divisibility by 9:
#     A number is divisible by 9 if and only if the sum of its digits is divisible by 9.
#   - For each digit in input string:
#     - If it's 0,1,2,3, then we can transform it to 0,1,4,9 respectively.
#     - We want to minimize how much we "add" or "increase" the sum of digits modulo 9,
#       so that we can make it 0 mod 9.
#   - Use frequency count of '2' and '3', and compute:
#     f("2") - s % 3 >= (s + s % 3 * 2) % 9 - f("3") * 3
#   - The expression is compared against 0 to determine the result.
#
# Time Complexity: O(n), where n is total length of input across all test cases.
# Space Complexity: O(1), only fixed-size variables used.

for *n, _ in [*open(0)][1:]:
    f = n.count  # Count occurrences of characters in the string
    s = sum(map(int, n))  # Compute sum of digits
    print("NYOE S"[0 <= f("2") - s % 3 >= (s + s % 3 * 2) % 9 - f("3") * 3 :: 2])  # Output result based on condition


# https://github.com/VaHiX/codeForces/