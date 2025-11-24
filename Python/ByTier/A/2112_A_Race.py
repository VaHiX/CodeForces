# Problem: CF 2112 A - Race
# https://codeforces.com/contest/2112/problem/A

"""
Problem: Race
Algorithms/Techniques: Mathematical comparison, absolute difference

Time Complexity: O(1) - Constant time per test case as we perform only basic arithmetic operations.
Space Complexity: O(1) - Only using a constant amount of extra space.

The problem involves determining if Bob can choose a starting point such that he is guaranteed to reach the prize faster than Alice,
regardless of whether the prize drops at point x or y. 

Key insight:
- For Bob to always win, no matter where the prize is dropped (at x or y), 
  he must be able to pick a point such that:
  - Distance from Bob's point to x < Distance from Alice's point to x
  - Distance from Bob's point to y < Distance from Alice's point to y

This condition simplifies to checking whether the difference in distances (from Alice to x vs. Bob to x) 
and (from Alice to y vs. Bob to y) is consistent enough for a fixed choice of Bob's point.

The solution leverages this by comparing (a < x) == (a < y). 
If this condition holds true, it means both a and x are on the same side of y or vice versa,
ensuring a consistent strategy for Bob.
"""

for t in range(int(input())):
    a, x, y = map(int, input().split())  # Read Alice's position, and possible prize positions
    print("YES" if (a < x) == (a < y) else "NO")  # Check if Bob can guarantee faster reach


# https://github.com/VaHiX/codeForces/