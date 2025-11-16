# Problem: CF 866 A - Save the problem!
# https://codeforces.com/contest/866/problem/A

"""
Code Purpose:
This code generates a test case for the "Coin Change" problem where the number of ways to make change is given.
The approach is to use a greedy method where we construct a set of denominations such that the number of combinations
matches the input. The algorithm uses a simple trick:
- For a given number A (number of ways), we can construct input as:
  - N = 2*A - 1 (the amount to make change for)
  - M = 2 (number of coin denominations)
  - Denominations = [1, 2]

This works because:
- If we have coins of denominations 1 and 2, and we need to make amount N = 2*A - 1,
  the number of ways to make that amount is exactly A.
  (This follows the pattern where the number of combinations for amount N with coins 1 and 2 is N//2 + 1)

Time Complexity: O(1)
Space Complexity: O(1)
"""

# Read the number of ways
A = int(input())

# Output the constructed test case
print(2 * A - 1, 2)  # N = 2*A - 1, M = 2
print(1, 2)  # Denominations are 1 and 2


# https://github.com/VaHiX/CodeForces/