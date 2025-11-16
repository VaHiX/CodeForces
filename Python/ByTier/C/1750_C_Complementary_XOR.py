# Problem: CF 1750 C - Complementary XOR
# https://codeforces.com/contest/1750/problem/C

"""
Algorithm: Complementary XOR
Technique: Bit manipulation and regex pattern matching
Time Complexity: O(n) for each test case, where n is the length of strings
Space Complexity: O(n) for storing the patterns and intermediate results

This solution leverages the fact that the problem can be reduced to a bit manipulation task.
By XORing the two binary strings and using regex to find contiguous segments of '1's,
we can determine a sequence of operations to make both strings all zeros.
The key insight is that the XOR of the two strings encodes the necessary changes,
and the pattern of 1s in the XOR result guides the operations.
"""

import re

f = open(0)
I = lambda: next(f, "0 ")[:-1]
I()
while n := int(I()):
    # XOR the two binary strings to get a pattern of differences
    i = int(a := I(), 2) ^ int(I(), 2)
    # Find all contiguous segments of '1' in the XOR result
    c = [m.span() for m in re.finditer("1+", a)]
    # Adjust the operation list based on the number of 1s and the length of string
    # The added operations ensure the final result is all zeros
    c += (len(c) + i) % 2 * [(0, 1), (0, n), (1, n)]
    # Print result based on whether operations are valid for transformation
    print(
        *(["YES", len(c)] + [f"{x [0 ]+1 } {x [1 ]}" for x in c], ["NO"])[
            1 < i + 1 < 1 << n
        ]
    )


# https://github.com/VaHiX/CodeForces/