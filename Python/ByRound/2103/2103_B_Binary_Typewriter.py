# Problem: CF 2103 B - Binary Typewriter
# https://codeforces.com/contest/2103/problem/B

# B. Binary Typewriter
# Purpose: Given a binary string, compute the minimum cost of typing it with a typewriter that has two buttons (0 and 1),
#          where initial finger position is on button 0. You may reverse at most one substring before typing.
#          Cost = number of operations to type the string,
#                where operation 1 = press current button, operation 2 = move finger to other button.
#
# Algorithm:
# - The cost without any reversal is determined by counting transitions (i.e., "10" or "01") and 
#   adding 1 for the first character.
# - When we reverse a substring, we consider changing one transition from "10" to "01", which reduces
#   the total cost by 2 (if we eliminate two transitions or fix two edges).
# - To optimize: compute current cost, and check all possibilities of reversing substrings to reduce it.
# - The final optimized result is calculated based on:
#     - The number of transitions "10" in the string
#     - Whether we can reduce by flipping a segment
#     - Adjusting for initial conditions (e.g., if start with '0', finger starts at 0, so no cost)
#
# Time Complexity: O(n) per test case (single pass through string)
# Space Complexity: O(1) (only using constant extra space)

for s in [*open(0)][2::2]:  # Read all lines and take every second line starting from index 2
    k = s.count("10") * 2 + int(s[-2])  # Count transitions of "10", multiply by 2, add last char's binary value (0 or 1)
    print(len(s) + k - (k > 1) - (k > 2) - 1)  # Adjust the cost based on transition count and output


# https://github.com/VaHiX/codeForces/