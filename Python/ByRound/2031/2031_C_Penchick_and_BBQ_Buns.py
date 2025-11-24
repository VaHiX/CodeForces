# Problem: CF 2031 C - Penchick and BBQ Buns
# https://codeforces.com/contest/2031/problem/C

"""
Algorithm/Technique:
- The solution generates a valid assignment of fillings to buns such that:
  1. Each filling is used at least twice, or not at all.
  2. Any two buns with the same filling are spaced by a perfect square distance.
- For odd n:
  - If n < 27, it's impossible to construct a valid assignment.
  - Otherwise, we use a predefined pattern for the first 27 elements and then extend it.
    - The pattern ensures spacing between same fillings is always a perfect square.
- For even n:
  - A simple linear pattern that assigns fillings such that spacing condition is satisfied.
  - The pattern is generated using the formula j // 2 + 1 for j in range(n).

Time Complexity: O(n) per test case. We construct the output list in linear time.
Space Complexity: O(n) for storing the output list.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    if n % 2:  # If n is odd
        if n < 27:
            print(-1)
        else:
            # Predefined pattern for the first 27 elements
            out = [
                1,
                2,
                2,
                3,
                3,
                4,
                4,
                5,
                5,
                1,  # This ensures perfect square spacing
                6,
                6,
                7,
                7,
                8,
                8,
                9,
                9,
                10,
                10,
                11,
                11,
                12,
                13,
                13,
                1,   # Start of another perfect square spacing
                12,
            ]
            st = 28  # Start value for extending the pattern
            while len(out) < n:  # Extend the pattern until we reach length n
                out.append(st // 2)
                st += 1
            print(*out)
    else:  # If n is even
        # Simple pattern where filling is j//2 + 1 for j in range(n)
        print(*[j // 2 + 1 for j in range(n)])


# https://github.com/VaHiX/CodeForces/