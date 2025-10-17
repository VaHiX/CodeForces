# Problem: CF 1772 A - A+B?
# https://codeforces.com/contest/1772/problem/A

# ==============================================================================
# Code Purpose: Evaluates simple addition expressions of two single-digit integers
# Algorithms/Techniques: String parsing, integer conversion, arithmetic operation
# Time Complexity: O(t) where t is the number of test cases
# Space Complexity: O(1) - constant extra space
# ==============================================================================

t = int(input())  # Read number of test cases
for _ in range(t):  # Process each test case
    expression = input()  # Read the expression string (e.g., "4+2")
    plus_index = expression.index('+')  # Find position of '+' character
    a = int(expression[:plus_index])  # Extract first number (before '+')
    b = int(expression[plus_index + 1:])  # Extract second number (after '+')
    print(a + b)  # Print the sum of the two numbers


# https://github.com/VaHiX/codeForces/