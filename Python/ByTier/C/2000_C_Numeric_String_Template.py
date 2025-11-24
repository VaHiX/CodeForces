# Problem: CF 2000 C - Numeric String Template
# https://codeforces.com/contest/2000/problem/C

"""
C. Numeric String Template
Algorithm: Check if a string matches a numeric template by verifying bijective mapping.
Time Complexity: O(n + sum of string lengths) per test case
Space Complexity: O(n) per test case

The solution uses a bijection check between the elements of the array and characters of the string:
1. Length match check.
2. Bijectivity via zip and set operations to ensure one-to-one mapping.

Approach:
- For each query string, verify:
  - Same length as template array
  - Unique elements in both template and string
  - No two different elements map to same character or vice versa
"""

def solve():
    n, v = int(input()), input().split()  # Read array size and elements
    q = int(input())                      # Number of strings to check
    s = [input() for _ in range(q)]       # Read all query strings
    vs = {*v}                             # Create set of unique elements from template
    return "\n".join(
        ["NO", "YES"][
            len(x) == len(v) and                  # String length equals array length
            len(vs) == len({*zip(x, v)}) and      # Bijection: unique pairs (char, num)
            len({*x}) == len(vs)                  # Unique chars equal unique nums
        ]
        for x in s                               # For each string
    )

[print(solve()) for x in range(int(input()))]  # Process all test cases


# https://github.com/VaHiX/codeForces/