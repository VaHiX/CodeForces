# Problem: CF 2074 E - Empty Triangle
# https://codeforces.com/contest/2074/problem/E

"""
E. Empty Triangle

Purpose:
This code solves an interactive problem where the goal is to find a triangle formed by three of n given points 
that does not contain any other point inside it (i.e., an "empty" triangle). It uses a randomized approach to 
query triangles and iteratively refine the search.

Algorithms/Techniques:
- Randomized querying with adaptive feedback from the interactor
- Maintains a list `p` of three indices representing points forming a candidate triangle
- Replaces one point in `p` randomly with a point returned by the interactor if it's not 0 (indicating a point inside the triangle)
- Stops when a query returns 0, which means no point is inside the current triangle

Time Complexity: O(1) per test case since at most 75 queries are made and n up to 1500 doesn't directly affect complexity.
Space Complexity: O(1) as only a fixed-size list `p` of three integers is used.

Interaction:
- Queries are made in the form "? i j k"
- Answers are given in the form "! i j k" when a valid empty triangle is found
"""

import random

for _ in range(int(input())):
    n = int(input())
    p = [1, 2, 3]  # Start with a fixed initial triangle (indices 1, 2, 3)
    for i in range(75):  # At most 75 queries allowed
        print(f"? {p[0]} {p[1]} {p[2]}")  # Query current triangle formed by indices in p
        nw = int(input())  # Read feedback from interactor
        if nw == 0:
            break  # No point inside the triangle, we found a valid result
        p[random.randint(0, 2)] = nw  # Replace one random index with the returned point to explore further
    print(f"! {p[0]} {p[1]} {p[2]}")  # Output the final candidate for an empty triangle



# https://github.com/VaHiX/codeForces/