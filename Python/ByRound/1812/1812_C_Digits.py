# Problem: CF 1812 C - Digits
# https://codeforces.com/contest/1812/problem/C

"""
Algorithm: Product of digits
Time Complexity: O(1) per test case (since n is bounded by 155 and each test case processes at most 9 inputs)
Space Complexity: O(1) (only using fixed size variables and array of size 155)

This code calculates the product of digits for each test case. 
For each test case, it reads the number of digits (v) and then reads v integers,
computing their product and printing the result.
"""
n = "31415926535897932384626433832795"
a = [int(i) for i in n]  # Predefined array of digits, likely used for test case counts
t = int(input())  # Read number of test cases
for kase in range(t):  # Process each test case
    res = 1  # Initialize result to 1 for multiplication
    v = a[kase]  # Get the number of digits for current test case from predefined array
    for i in range(v):  # Read v integers and calculate their product
        cur = int(input())  # Read current integer
        res *= cur  # Multiply current integer with result
    print(res)  # Print the final product


# https://github.com/VaHiX/CodeForces/