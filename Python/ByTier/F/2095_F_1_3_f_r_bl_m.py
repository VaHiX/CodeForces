# Problem: CF 2095 F - ⅓ оf а Рrоblеm
# https://codeforces.com/contest/2095/problem/F

"""
Problem: F. ⅓ оf а Рrоblеm
Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage

Algorithms/Techniques: Simple arithmetic expression evaluation

The code computes a mathematical expression involving two integer inputs a and b.
It performs basic arithmetic operations including multiplication, subtraction, 
absolute value calculation, and addition.
"""

a, b = map(int, input().split())  # Read two integers from input and assign them to variables a and b
print(12 * a + abs(a - b) + (15 * a - 3 * b) * b + 2)  # Compute and print the result of the arithmetic expression


# https://github.com/VaHiX/codeForces/