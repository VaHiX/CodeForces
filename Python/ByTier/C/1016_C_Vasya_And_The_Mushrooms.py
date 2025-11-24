# Problem: CF 1016 C - Vasya And The Mushrooms
# https://codeforces.com/contest/1016/problem/C

"""
C. Vasya And The Mushrooms

Purpose:
This code solves the problem of finding the maximum total weight of mushrooms Vasya can collect 
by traversing a 2-row grid of n cells, moving only to adjacent cells and visiting each cell exactly once.

The solution uses a greedy approach combined with prefix sum optimizations to efficiently compute
the best possible traversal path.

Algorithms/Techniques:
- Dynamic programming on grid traversal paths
- Prefix sums for optimizing movement cost calculations
- Greedy optimization based on relative speeds of mushroom growth

Time Complexity: O(n)
Space Complexity: O(n)

Input Format:
- First line: n (number of cells per row)
- Second line: n integers representing mushroom growth rate in first row
- Third line: n integers representing mushroom growth rate in second row

Output:
- Maximum total weight of mushrooms that can be collected
"""

R, G = lambda: map(int, input().split()), range
(n,) = R()
g = [[*R()] for _ in G(2)]
p = [0] * 2
s = sum(2 * j * g[j & 1][j] + (2 * j + 1) * g[(j + 1) & 1][j] for j in G(n))  # Initialize total weight with base path
z = s  # Keep track of maximum value seen so far

# Compute incremental gains from changing the path at each step
for j in G(1, n):
    # Accumulate movement cost differences for current position
    for i in G(2):
        p[i] += 2 * j * (g[1 ^ i][n - 1 - j] - g[i][n - j])
    
    # Add the change in weight due to path modification
    s += p[j & 1 ^ (n + 1) & 1]
    z = max(z, s)  # Update maximum if new path is better

print(z)


# https://github.com/VaHiX/codeForces/