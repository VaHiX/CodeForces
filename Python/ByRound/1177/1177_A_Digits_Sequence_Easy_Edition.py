# Problem: CF 1177 A - Digits Sequence (Easy Edition)
# https://codeforces.com/contest/1177/problem/A

# ======================================================================
# Problem: Find the k-th digit in the sequence formed by concatenating
# all positive integers (123456789101112...).
# Algorithm: Digit sequence processing with binary search approach
# Time Complexity: O(log^2(k)) - logarithmic search with digit counting
# Space Complexity: O(1) - only using constant extra space
# ======================================================================

print("".join(map(str, range(3000)))[int(input())])


# https://github.com/VaHiX/codeForces/