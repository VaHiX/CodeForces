# Problem: CF 2167 A - Square?
# https://codeforces.com/contest/2167/problem/A

"""
Purpose: Determine if four given stick lengths can form a square.
         A square requires all four sides to be of equal length.

Algorithm:
    - Read four integers representing stick lengths.
    - Check if all four integers are equal.
    - If yes, output "YES", otherwise "NO".

Time Complexity: O(1) - Constant time operations.
Space Complexity: O(1) - Only using a fixed amount of extra space.
"""

import sys

input = sys.stdin.readline


def solve():
    # Read the four stick lengths
    a, b, c, d = map(int, input().split())
    # Check if all sides are equal (condition for forming a square)
    return "YES" if a == b == c == d else "NO"


# Read number of test cases
T = int(input())
# Process all test cases and store results
out = [solve() for _ in range(T)]
# Print all results
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/