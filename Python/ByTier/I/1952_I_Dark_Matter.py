# Problem: CF 1952 I - Dark Matter
# https://codeforces.com/contest/1952/problem/I

"""
Problem: Dark Matter
Algorithms: Mathematical computation with basic arithmetic operations
Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage

The problem appears to be a mathematical expression evaluation where:
- Input is parsed as a string expression "a + b" 
- Values are extracted and processed through a complex formula
- The final result is computed and printed
"""

p = input().split()  # Split input string by whitespace to get tokens
a, b = int(p[0]), int(p[2])  # Extract first and third tokens as integers (assuming format "a + b")
res = (a**2 + b**2) + (a - b) + abs(a) * (2 * b) - (a * b + 2)  # Compute complex mathematical expression
print(a + b + res)  # Print the final result


# https://github.com/VaHiX/CodeForces/