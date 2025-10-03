# Problem: CF 2074 F - Counting Necessary Nodes
# https://codeforces.com/contest/2074/problem/F

"""
F. Counting Necessary Nodes

Purpose:
This code computes the minimum number of nodes required in a quadtree to exactly cover a given rectangular region [l1, r1] × [l2, r2].

The algorithm uses inclusion-exclusion principle over all possible quadtree levels (bit lengths), where for each level we count how many nodes contribute and adjust overlaps.

Algorithms/Techniques:
- Inclusion-Exclusion Principle
- Bit manipulation to iterate through powers of 2 (quadtree levels)
- Coordinate compression based on powers of 2

Time Complexity: O(log(min(r1 - l1, r2 - l2)))
Space Complexity: O(1)

Input Format:
Each test case contains four integers l1, r1, l2, r2 representing the boundaries of a rectangle.

Output Format:
For each test case, output the minimum number of nodes needed to cover the rectangle exactly.
"""

import sys

I = input = sys.stdin.readline
for _ in range(int(I())):
    l, r, d, u = map(int, I().split())
    ans = (r - l) * (u - d)  # Start with total area (base case: all 1x1 nodes)
    
    # Iterate over all possible quadtree levels
    for i in range(1, min(r - l, u - d).bit_length()):
        s = 1 << i  # Side length of current level (power of 2)
        # Count full squares at this level that intersect with the rectangle
        # Subtract 3 times number of such full squares to account for overcounting in inclusion-exclusion
        ans -= 3 * (r // s - (l + s - 1) // s) * (u // s - (d + s - 1) // s)
    
    sys.stdout.write(f"{ans}\n")


# https://github.com/VaHiX/codeForces/