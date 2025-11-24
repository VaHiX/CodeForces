# Problem: CF 2038 M - Royal Flush
# https://codeforces.com/contest/2038/problem/M

"""
Minimum Expected Turns to Royal Flush

This problem involves calculating the expected number of turns to achieve a Royal Flush
in a card game with n suits. A Royal Flush consists of 10, J, Q, K, A all of the same suit.

The solution uses a precomputed lookup table based on dynamic programming and game theory
to compute the expected number of turns for 1, 2, 3, and 4 suits.

Time Complexity: O(1) - constant time lookup
Space Complexity: O(1) - constant space for the lookup table

Algorithms/Techniques:
- Precomputed Dynamic Programming
- Game Theory Expected Value Calculation
"""

a = 3.598290598, 8.067171309, 12.423075, 16.63664
print(a[int(input()) - 1])


# https://github.com/VaHiX/CodeForces/