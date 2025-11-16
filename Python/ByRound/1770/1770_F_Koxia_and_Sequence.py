# Problem: CF 1770 F - Koxia and Sequence
# https://codeforces.com/contest/1770/problem/F

"""
Algorithm: Bitwise manipulation and enumeration
Purpose: To compute the total bitwise XOR of scores of all good arrays satisfying:
         - Sum of elements = x
         - Bitwise OR of elements = y
         - Score = XOR of elements
Time Complexity: O(log^2(y) * log(x))
Space Complexity: O(1)

The solution leverages the fact that for odd n, the contribution of each bit 
to the final answer can be determined by analyzing how the bits of y and x interact.
We enumerate bits of y and check conditions on x to determine valid contributions.
"""

import sys

input = sys.stdin.readline

n, x, y = map(int, input().strip().split())

ans = 0

# Only odd n can contribute to the result
if n % 2 == 1:
    s = y
    while s > 0:

        p2 = 1
        # Iterate through powers of 2 up to s and x
        while p2 <= s and p2 <= x:

            # If bit p2 is set in s and the condition holds, XOR it into the answer
            if s & p2 > 0 and n * s - p2 & x - p2 == x - p2:
                ans ^= p2

            p2 *= 2

        # Move to next lower value of s (bitwise AND with y)
        s = s - 1 & y

print(ans)


# https://github.com/VaHiX/CodeForces/