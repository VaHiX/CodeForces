# Problem: CF 1950 F - 0, 1, 2, Tree!
# https://codeforces.com/contest/1950/problem/F

"""
Code Purpose:
This solution determines the minimum height of a rooted tree given the counts of vertices with 0, 1, and 2 children.
The problem is solved using a mathematical approach based on the constraints of tree structure and optimal packing.

Algorithms/Techniques:
- Mathematical reasoning to determine minimum tree height from given vertex counts
- Bit manipulation (`a.bit_length()`) to compute the smallest power of 2 greater than or equal to a
- Arithmetic calculation to check for feasible tree structure and compute minimal height

Time Complexity: O(1) per test case
Space Complexity: O(1)

The key insight is:
- For a valid tree, the number of edges must be exactly (a + b + c - 1)
- Each vertex with 2 children contributes 2 edges, 1 child contributes 1 edge, 0 children contribute 0 edges
- So total edges = 2*a + b
- Equating: 2*a + b = a + b + c - 1 -> a = c - 1
- Then we simulate optimal packing to determine minimum height based on how many vertices
  can be placed at each level.
"""

for e in [*open(0)][1:]:
    a, b, c = map(int, e.split())
    l = a.bit_length()  # Calculates the bit length of a, which is floor(log2(a)) + 1
    print(c - a - 1 and -1 or (b - 2**l + a + c) // c + l)  # Computes the minimum height or -1 if invalid


# https://github.com/VaHiX/CodeForces/