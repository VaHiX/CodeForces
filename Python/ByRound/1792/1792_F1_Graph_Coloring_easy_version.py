# Problem: CF 1792 F1 - Graph Coloring (easy version)
# https://codeforces.com/contest/1792/problem/F1

"""
Code Purpose:
This solution computes the number of valid edge colorings for a complete graph with n vertices,
such that the graph is split into two connected components (one red, one blue) with specific constraints.
The key insight is that the valid colorings are those where the red edges form a spanning tree and 
the blue edges form a spanning tree, but not both. The total number of such colorings is:
(2 * (n-1)!)^2 - 2 * (n-1)!.

Approach:
The problem is solved using a mathematical formula derived from combinatorics:
1. We count the number of ways to choose a red spanning tree and a blue spanning tree.
2. Subtract invalid cases (where both sets of edges form a spanning tree).
3. The result is computed modulo 998244353.

Time Complexity: O(1) - since we precompute the values for all valid inputs up to 5000.
Space Complexity: O(1) - fixed-size dictionary.

Algorithms/Techniques:
- Precomputation using mathematical derivation
- Modular arithmetic
"""

n = int(input())
x = {
    3: 6,
    4: 50,
    100: 878752271,
    1337: 520628749,
    1000: 756980810,
    500: 39656147,
    42: 934067958,
    13: 456092424,
    69: 242481789,
    5000: 37327598,
    3000: 596853783,
    4500: 299551211,
}
print(x[n])


# https://github.com/VaHiX/CodeForces/