# Problem: CF 2009 A - Minimize!
# https://codeforces.com/contest/2009/problem/A

"""
Problem: Minimize! (A. Minimize!)
Algorithm: Mathematical optimization
Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage

The expression (c-a)+(b-c) simplifies to b-a, which is independent of c.
So the minimum value is always b-a for any valid c in range [a,b].
"""

for _ in range(int(input())):  # Read number of test cases and iterate
    a, b = map(int, input().split())  # Read a and b from input
    print(b - a)  # Print the result which is always b-a


# https://github.com/VaHiX/codeForces/