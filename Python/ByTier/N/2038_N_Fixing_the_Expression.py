# Problem: CF 2038 N - Fixing the Expression
# https://codeforces.com/contest/2038/problem/N

"""
Problem: Fixing the Expression
Purpose: Given a string expression of the form "digit1<digit2", "digit1>digit2", or "digit1=digit2", 
         modify the expression to make it true by changing as few characters as possible.

Algorithms/Techniques: 
- Direct comparison of numeric values.
- Simple conditional logic to check and adjust the comparison operator.

Time Complexity: O(1) - The input size is fixed (3 characters), so all operations are constant time.
Space Complexity: O(1) - Only a fixed amount of additional space is used.

The code compares the first and third characters (digits) and outputs the correct expression
by choosing the appropriate comparison operator based on the numerical relationship.
"""

t = int(input())  # Read number of test cases
for i in range(t):
    x = input()  # Read the expression string
    
    # Compare the first and third characters (the digits)
    if x[0] > x[2]:  # If first digit is greater than second
        print(x[0] + ">" + x[2])  # Keep the '>' operator
    elif x[0] < x[2]:  # If first digit is less than second
        print(x[0] + "<" + x[2])  # Keep the '<' operator
    else:  # If first digit equals second
        print(x[0] + "=" + x[2])  # Keep the '=' operator


# https://github.com/VaHiX/CodeForces/