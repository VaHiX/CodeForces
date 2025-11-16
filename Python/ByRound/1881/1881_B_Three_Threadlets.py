# Problem: CF 1881 B - Three Threadlets
# https://codeforces.com/contest/1881/problem/B

"""
Code Purpose:
This code determines whether it's possible to make all three threadlets of equal length by performing at most three cutting operations. Each operation allows cutting a threadlet into two positive integer-length threadlets.

Algorithms/Techniques:
- Sorting the threadlet lengths to simplify analysis.
- Using logical conditions to check if the threadlets can be made equal within 3 operations.
- Precomputed patterns based on how many cuts are needed to make lengths equal.

Time Complexity: O(t), where t is the number of test cases. Sorting is constant time (3 elements), and each check is O(1).
Space Complexity: O(1), excluding the input/output buffer. The list 'log' stores results, but it's bounded by the number of test cases.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


II = lambda: int(input())
MII = lambda: map(int, input().split())
LMII = lambda: list(MII())
SMII = lambda: sorted(MII())

log = list()

for _ in range(II()):
    a, b, c = SMII()  # Sort the lengths to simplify logic

    # Check all valid conditions where threadlets can be made equal in at most 3 cuts
    good = (
        a == c  # All three already equal
        or a == b  # Two equal, check if third can be made equal with at most 3 cuts
        and (c == 2 * a or c == 3 * a or c == 4 * a)  # Third matches expected values after up to 3 cuts
        or b == c  # Two equal, first can be made equal with at most 3 cuts
        and c == 2 * a  # This implies we have a = b = c/2
        or b == 2 * a  # First and middle, check if third fits pattern
        and c == 3 * a  # This implies we have a = a, 2*a = b, 3*a = c
    )

    if good:
        log.append("YES")
    else:
        log.append("NO")


sys.stdout.write("\n".join(log))


# https://github.com/VaHiX/CodeForces/