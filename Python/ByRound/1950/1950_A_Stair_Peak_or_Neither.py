# Problem: CF 1950 A - Stair, Peak, or Neither?
# https://codeforces.com/contest/1950/problem/A

"""
Code purpose: Determine if three given digits form a stair, peak, or neither.
Algorithms/Techniques: Simple conditional checks to compare three values
Time Complexity: O(1) - Constant time as we perform a fixed number of comparisons
Space Complexity: O(1) - Constant space as we only store a few variables
"""

t = int(input())  # Read number of test cases
for _ in range(t):  # Process each test case
    a, b, c = map(int, input().split())  # Read the three digits
    if a < b < c:  # Check if digits form a stair (strictly increasing)
        print("STAIR")
    elif a < b > c:  # Check if digits form a peak (b is greater than both a and c)
        print("PEAK")
    else:  # If neither condition is met
        print("NONE")


# https://github.com/VaHiX/CodeForces/