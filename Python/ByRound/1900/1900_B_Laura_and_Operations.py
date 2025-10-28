# Problem: CF 1900 B - Laura and Operations
# https://codeforces.com/contest/1900/problem/B

"""
Code Purpose:
This code solves the problem of determining whether it's possible to reduce a set of digits (1, 2, and 3) 
to only one type of digit through a series of operations. Each operation involves selecting two different 
digits and replacing them with the third digit. 

The solution leverages the parity (odd/even nature) of the differences between counts of each pair of digits.

Algorithms/Techniques:
- Mathematical analysis of parity (even/odd)
- Observation that each operation reduces the count of two types of digits by 1 and increases the third by 1
- Key insight: For a specific digit type to remain, the difference in counts between the other two types must be even
- Time and Space Complexity:
  - Time Complexity: O(t), where t is the number of test cases, as we process each test case in constant time
  - Space Complexity: O(1) excluding the space for output, as we only store a constant number of variables
"""

import sys


def solve():
    t = int(sys.stdin.readline())
    results = []
    for _ in range(t):
        a, b, c = map(int, sys.stdin.readline().split())
        # Check if it's possible to reduce to only '1's
        # The difference between 'b' and 'c' must be even for this to be possible
        res1 = 1 if (b - c) % 2 == 0 else 0
        # Check if it's possible to reduce to only '2's
        # The difference between 'a' and 'c' must be even for this to be possible
        res2 = 1 if (a - c) % 2 == 0 else 0
        # Check if it's possible to reduce to only '3's
        # The difference between 'a' and 'b' must be even for this to be possible
        res3 = 1 if (a - b) % 2 == 0 else 0
        results.append(f"{res1} {res2} {res3}")
    print("\n".join(results))


solve()


# https://github.com/VaHiX/CodeForces/