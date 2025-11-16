# Problem: CF 1936 A - Bitwise Operation Wizard
# https://codeforces.com/contest/1936/problem/A

"""
Algorithm: Bitwise Operation Wizard
Purpose: Find two indices i and j such that p[i] XOR p[j] is maximized using at most 3n queries.
Technique: 
- Use queries to find the maximum possible value of p[i] XOR p[j] by leveraging OR operations.
- The key idea is to determine the maximum value of a number and then find another number 
  that maximizes XOR with it.
- First, find the index of the maximum element (in terms of bit representation).
- Then, find two numbers that result in the maximum XOR.
Time Complexity: O(n) amortized for each test case due to the number of queries.
Space Complexity: O(1) as we use constant extra space.
"""

import os
import sys

input = sys.stdin.buffer.readline


def f(a, b, c, d):
    # Send a query with indices a, b, c, d and return the comparison result
    os.write(1, b"%s %d %d %d %d\n" % (p, a, b, c, d))
    return input().rstrip().decode()


def g(a, b):
    # Output the final answer with indices a, b
    os.write(1, b"%s %d %d\n" % (q, a, b))
    return


t = int(input())
p, q = "?".encode(), "!".encode()
for _ in range(t):
    n = int(input())
    x = 0  # Initialize x to 0
    # Find the index of the element with the highest value (in terms of binary representation)
    for y in range(1, n):
        c = f(x, x, y, y)  # Query to compare (p[x] | p[x]) vs (p[y] | p[y])
        if c == "<":  # If p[y] is greater than p[x]
            x = y  # Update x to y
    y = x  # Initialize y to x
    u = []  # List to store indices that are equal to the maximum
    # Find all indices whose OR with x gives the maximum OR value
    for z in range(n):
        c = f(x, y, x, z)  # Query to compare (p[x] | p[y]) vs (p[x] | p[z])
        if c == "<":  # If (p[x] | p[z]) > (p[x] | p[y])
            y = z  # Update y to z
            u = [y]  # Reset u with z
        elif c == "=":  # If (p[x] | p[z]) == (p[x] | p[y])
            u.append(z)  # Add z to u
    y = u[0]  # Initialize y to the first element in u
    # Final step: Find the index in u that gives the maximum XOR with x
    for z in u:
        c = f(y, y, z, z)  # Query to compare (p[y] | p[y]) vs (p[z] | p[z])
        if c == ">":  # If p[y] > p[z]
            y = z  # Update y to z
    g(x, y)  # Output the final result
exit()


# https://github.com/VaHiX/CodeForces/