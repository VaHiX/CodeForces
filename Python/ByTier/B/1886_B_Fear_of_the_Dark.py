# Problem: CF 1886 B - Fear of the Dark
# https://codeforces.com/contest/1886/problem/B

"""
Algorithm: 
This problem involves finding the minimum radius w such that two lanterns at points A and B can fully illuminate a path from the origin O(0, 0) to point P(px, py). The illumination of each lantern is a circle of radius w centered at the lantern's position. 

Approach:
1. Compute distances from O and P to each lantern (AO, AP, BO, BP).
2. Compute the distance between the two lanterns (AB), and calculate the midpoint distance (rt = AB / 2).
3. For each candidate radius r from sorted list [AP, AO, BP, BO, rt]:
   - Check if we can reach P with radius r such that either:
     - Both O and P are within radius r of the same lantern (AP <= r and AO <= r) or
     - Both O and P are within radius r of the other lantern (BP <= r and BO <= r)
   - Or, if r is greater than or equal to rt, then:
     - At least one of (O or P) is illuminated by one lantern, and the other by the second one.
4. Output the minimum such valid r.

Time Complexity: O(1) per test case, since all operations involve fixed number of comparisons and calculations.
Space Complexity: O(1), since only a fixed-size list 'log' is used for output.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


II = lambda: int(input())
MII = lambda: map(int, input().split())
LMII = lambda: list(MII())
SLMII = lambda: sorted(MII())

log = list()

for _ in range(II()):
    px, py = MII()
    ax, ay = MII()
    bx, by = MII()

    # Calculate distance from O to P via A and B
    AP = ((ax - px) ** 2 + (ay - py) ** 2) ** 0.5
    AO = (ax**2 + ay**2) ** 0.5
    BP = ((bx - px) ** 2 + (by - py) ** 2) ** 0.5
    BO = (bx**2 + by**2) ** 0.5
    # Distance between two lanterns
    rt = (((ax - bx) ** 2 + (ay - by) ** 2) ** 0.5) / 2

    # Check all possible radius values in sorted order
    for r in sorted([AP, AO, BP, BO, rt]):
        # If r is less than midpoint distance, check if both O and P are within it from same lantern
        if r < rt and (AP <= r and AO <= r or BP <= r and BO <= r):
            log.append(r)
            break
        # If r is greater or equal to midpoint distance, check if O-P path can be illuminated by two separate lanterns
        if r >= rt and ((AP <= r or BP <= r) and (AO <= r or BO <= r)):
            log.append(r)
            break

sys.stdout.write("\n".join(map(str, log)))


# https://github.com/VaHiX/CodeForces/