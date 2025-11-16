# Problem: CF 1499 A - Domino on Windowsill
# https://codeforces.com/contest/1499/problem/A

"""
Code Purpose:
This code solves the problem of determining whether it's possible to place all given white and black dominoes on a 2×n grid board. The grid has the first k1 cells of the first row and first k2 cells of the second row colored white, with the rest black. Dominoes can be placed horizontally or vertically, and each domino must cover two adjacent cells of the same color.

The solution works by:
1. Calculating the total number of white cells (k1 + k2)
2. Calculating the total number of black cells (2*n - k1 - k2)
3. Checking if the number of dominoes needed (w and b) can fit into the available cells of their respective colors

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only a few variables are used
"""

for t in range(int(input())):
    n, k1, k2 = map(int, input().split())  # Read n, k1, k2
    w, b = map(int, input().split())       # Read w, b
    # Check if white dominoes can be placed (each needs 2 white cells)
    # Check if black dominoes can be placed (each needs 2 black cells)
    print("YES") if w * 2 <= k1 + k2 and b * 2 <= n * 2 - k1 - k2 else print("NO")


# https://github.com/VaHiX/CodeForces/