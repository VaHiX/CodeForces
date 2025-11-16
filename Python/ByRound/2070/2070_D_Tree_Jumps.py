# Problem: CF 2070 D - Tree Jumps
# https://codeforces.com/contest/2070/problem/D

"""
D. Tree Jumps

Purpose:
This code solves the problem of counting valid vertex sequences in a rooted tree,
where a chip starts at the root and can only move to vertices at distance +1 from current position,
with some restrictions on movement (not to direct neighbors unless at the root).

Algorithms/Techniques:
- Tree traversal to compute depth(levels) of each node
- Dynamic programming approach over levels to count valid sequences
- Modular arithmetic to avoid overflow

Time Complexity: O(n) per test case, where n is number of nodes.
Space Complexity: O(n) for storing parent, level and counter arrays.

Input Format:
- First line contains t (number of test cases)
- For each test case:
  - First line contains n (number of nodes)
  - Second line contains n-1 integers representing parents of nodes 2 to n

Output Format:
- For each test case, print the number of valid sequences modulo 998244353
"""

for _ in range(int(input())):
    n = int(input())
    parents = [0, 1] + [*map(int, input().split())]  # parents[1] = 1 (root), parents[i] = parent of node i
    levels = [0, 1] + [0 for _ in range(n - 1)]      # levels[i] = depth of node i
    level_ctr = [0, 1] + [0 for _ in range(n - 1)]   # level_ctr[i] = count of nodes at depth i

    # Compute the level (depth) of each node
    for i in range(2, n + 1):
        levels[i] = levels[parents[i]] + 1  # Level is parent's level + 1
        level_ctr[levels[i]] += 1           # Increment counter for current level

    # Reverse the level counter to process from deepest level to shallowest (bottom-up)
    level_ctr, a = level_ctr[::-1], 0

    # Dynamic programming: compute result by processing levels in reverse order
    # For each level, update 'a' based on number of nodes at that level
    for i in range(n - 1):
        a = a * (level_ctr[i] - 1) + level_ctr[i]  # Transition formula

    print((a + 1) % 998244353)  # Add 1 to include empty sequence, mod by 998244353


# https://github.com/VaHiX/codeForces/