# Problem: CF 2171 A - Shizuku Hoshikawa and Farm Legs
# https://codeforces.com/contest/2171/problem/A

"""
Task: Count the number of valid configurations of chickens and cows given total number of legs.

Approach:
- Let x = number of chickens (2 legs each)
- Let y = number of cows (4 legs each)
- We have the equation: 2x + 4y = n
- Simplify: x + 2y = n/2
- For valid integer solutions, n must be even.
- If n is even, then x = n/2 - 2y
- y can range from 0 to n/4 (since x >= 0)
- So number of valid configurations = n/4 + 1

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - only using a few variables
"""

for i in range(int(input())):  # Iterate over number of test cases
    n = int(input())  # Read number of legs
    if n & 1:  # Check if n is odd using bitwise AND
        print(0)  # If odd, no valid configuration exists
    else:
        print(n // 4 + 1)  # If even, calculate configurations


# https://github.com/VaHiX/CodeForces/