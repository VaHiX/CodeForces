# Problem: CF 2093 A - Ideal Generator
# https://codeforces.com/contest/2093/problem/A

# ================================================================================
# Problem: Determine if a number k is an "ideal generator".
# 
# An ideal generator k means that any integer n >= k can be represented as the sum
# of elements of a palindromic array of exactly k positive integers.
#
# Algorithm:
# - For k=1: Trivially true, any number n can be represented as [n].
# - For k=2: Need to check if every n >= 2 can be written as sum of two positive
#   integers in a palindromic way. Since we can use [1, n-1], and the array [a, b]
#   is palindromic iff a = b, i.e., [n/2, n/2] when n is even.
#   But it's not possible to express 3 as sum of two equal positive integers, so k=2 fails.
# - For odd k: If we have array of odd length, center element can be any value, and
#   others can adjust. So if k is odd, always possible for large enough n.
# - For even k > 2: Even length palindromic arrays require symmetric structure,
#   limiting representation space. The pattern holds when k >= 3 and k is odd.
#
# Time Complexity: O(1) per test case (constant time lookup or calculation).
# Space Complexity: O(1) (no extra space used).
# ================================================================================

for k in [*open(0)][1:]:  # Read all lines from stdin and skip first line
    print("YNEOS"[~int(k) & 1 :: 2])  # Bit manipulation trick for condition check:
                                      # If k is odd (k&1 == 1), output YES, otherwise NO.


# https://github.com/VaHiX/codeForces/