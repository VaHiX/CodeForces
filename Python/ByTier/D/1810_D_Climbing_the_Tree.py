# Problem: CF 1810 D - Climbing the Tree
# https://codeforces.com/contest/1810/problem/D

"""
Code Purpose:
This code solves the problem of determining the height of a tree and tracking snail climbing patterns.
Snails climb up 'a' meters during the day and slide down 'b' meters at night.
For each snail that claims to have climbed in 'n' days, we deduce a valid range of tree heights.
We maintain a range [lo, hi] of valid tree heights and update it with each new claim.
For queries about unknown snails, we calculate min and max possible days based on the valid height range.

Algorithms/Techniques:
- Binary search with range updates for valid tree height constraints
- Mathematical computation of climbing progress
- Constraint propagation to check contradiction and update ranges

Time Complexity: O(q * log(10^18)) where q is number of events
Space Complexity: O(1) excluding the output array
"""

import io
import os
import sys

try:
    Z = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
except:
    Z = lambda: sys.stdin.readline().encode()
Y = lambda: map(int, Z().split())

O = []
for _ in range(*Y()): # For each test case
    lo = -1  # Initialize lower bound of tree height
    hi = 10**18  # Initialize upper bound of tree height
    for __ in range(*Y()): # For each event in test case
        r = Y()
        if next(r) == 1: # Type 1 event: snail claims to finish in n days
            a, b, n = r
            if n == 1:
                # For 1 day, tree height must be between 1 and a meters
                vlo = 1
                vhi = a
            else:
                # Compute valid range for tree height given a, b, n:
                # After n-1 nights: climbed (n-2)*(a-b) meters
                # If he finishes on day n, he needs at least (a + (n-2)*(a-b)) meters
                # But he ends at a + (n-1)*(a-b) meters after climbing
                vlo = a + 1 + (n - 2) * (a - b)
                vhi = a + (n - 1) * (a - b)
            if lo == -1:
                # If first constraint, set bounds directly
                lo = vlo
                hi = vhi
            else:
                # Check for consistency with existing range
                if vlo > hi or vhi < lo:
                    # If new constraint is outside current range, contradiction
                    O.append("0 ") # Ignore the snail's claim
                    continue
                # Update the bounds to intersect with new constraint
                if lo < vlo:
                    lo = vlo
                if hi > vhi:
                    hi = vhi
            O.append("1 ") # Accept the snail's claim
        else: # Type 2 event: query for number of days required
            a, b = r
            # If the height lo is less than or equal to a, he finishes in 1 day
            if lo <= a:
                v1 = 1
            else:
                # Calculate minimum days needed for height lo
                # After first day: at most a meters
                # Then each day he climbs (a-b) meters net
                v1 = 2 + (lo - a - 1) // (a - b)
            # Same for maximum height
            if hi <= a:
                v2 = 1
            else:
                v2 = 2 + (hi - a - 1) // (a - b)
            if v1 != v2:
                # If min and max days differ, not uniquely determined
                O.append("-1 ") # Cannot determine precisely
            else:
                O.append(f"{v1 } ") # Unique number of days
    O.append("\n")
print("".join(O))


# https://github.com/VaHiX/CodeForces/