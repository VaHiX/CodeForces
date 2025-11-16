# Problem: CF 1743 A - Password
# https://codeforces.com/contest/1743/problem/A

# Flowerbox:
# Purpose: Calculate the number of valid 4-digit passwords where exactly two different digits appear,
#          each digit appearing exactly twice. Given a list of unused digits, find how many valid
#          4-digit combinations exist.
#
# Algorithm: For each test case:
#            1. Read n (number of unused digits) and the set of unused digits.
#            2. Generate all possible pairs of distinct digits from the remaining 10 - n digits.
#            3. For each such pair, calculate the number of ways to arrange them in a 4-digit password
#               where each digit appears exactly twice (i.e., choose positions for first digit: C(4,2) = 6).
#            4. Total is sum over all valid pairs.
#
# Time Complexity: O(n^2) per test case due to generating pairs of digits from available digits.
# Space Complexity: O(1), constant extra space (excluding input/output).

print("\n".join([str(3 * (10 - n) * (9 - n)) for n in map(int, [*open(0)][1::2])]))


# https://github.com/VaHiX/codeForces/