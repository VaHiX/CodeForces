# Problem: CF 2106 F - Goblin
# https://codeforces.com/contest/2106/problem/F

"""
F. Goblin

Purpose:
This code solves the problem of finding the maximum size of a connected component of '0's in an n×n grid,
where each row i represents a binary string formed by flipping the i-th character of the input string s.
The solution uses dynamic programming to track the longest path extending from each cell in two directions:
top-down and bottom-up, and computes the maximum over all cells.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Preprocessing of flip strings into a grid

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing top and bot arrays plus input

"""

import sys

input = sys.stdin.read
data = input().splitlines()
index = 0
t = int(data[index])
index += 1
for _ in range(t):
    n = int(data[index])
    index += 1
    s = " " + data[index]  # Add padding to make indexing easier (1-based)
    index += 1
    top = [0] * (n + 1)  # DP array for tracking top-down maximum path lengths
    bot = [0] * (n + 1)  # DP array for tracking bottom-up maximum path lengths
    ans = 0  # Store the maximum size of good set found so far
    
    for i in range(1, n + 1):
        if s[i] == "1":
            # If current character is '1', flip makes it '0'
            # So we can extend a path ending at previous row's rightmost cell
            top[i] = bot[i - 1] + 1
        else:
            # If current character is '0', flip makes it '1'.
            # For now, just propagate the longest path from left and use it as base for downward extensions.
            top[i] = top[i - 1] + (i - 1)
            bot[i] = bot[i - 1] + (n - i)
        ans = max(ans, max(top[i], bot[i]))
    print(ans)


# https://github.com/VaHiX/codeForces/