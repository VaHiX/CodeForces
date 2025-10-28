# Problem: CF 2035 B - Everyone Loves Tres
# https://codeforces.com/contest/2035/problem/B

# B. Everyone Loves Tres
# time limit per test1 second
# memory limit per test256 megabytes
#
# Problem:
# Given a positive integer n, find the smallest integer whose decimal representation has length n
# and consists only of 3s and 6s such that it is divisible by both 33 and 66.
# If no such integer exists, print -1.
#
# Algorithm:
# - For n=1: Impossible, since neither 3 nor 6 is divisible by 33.
# - For n=2: The number "66" is valid (divisible by both 33 and 66).
# - For n=3: No such number exists.
# - For n>=4:
#   - If n is odd, impossible (since 666...666 with odd length won't work).
#   - If n is even, build a string composed of "33" repeated (n//2) times and append "66" at the end,
#     or construct prefix of "3" and suffix of "66" if needed to meet exact n.
#
# Time Complexity: O(n), as we may need to construct a string of length n.
# Space Complexity: O(n), for storing the result string.

for n in [*map(int, open(0))][1:]:
    # Check for cases where no valid number exists:
    # - n=1 (no number made of 3s and 6s can be divisible by 33)
    # - n=3 (no such number exists)
    # - n is odd (length must be even to construct divisible numbers)
    print((1 != n != 3) - 1 or (n % 2 * "63" + "66").rjust(n, "3"))


# https://github.com/VaHiX/codeForces/