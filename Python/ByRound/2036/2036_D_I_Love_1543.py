# Problem: CF 2036 D - I Love 1543
# https://codeforces.com/contest/2036/problem/D

"""
D. I Love 1543
Algorithm: Spiral Traversal + Pattern Matching
Time Complexity: O(n * m) per test case, where n and m are dimensions of the carpet.
Space Complexity: O(n * m) for storing the input grid and intermediate string representations.

The problem requires counting how many times the pattern "1543" appears in the spiral traversal 
of layers of a grid. Each layer is traversed clockwise, and multiple occurrences (overlapping 
or non-overlapping) are counted. 

For each layer:
- Extract top row (left to right)
- Extract right column (top to bottom, skipping corners)
- Extract bottom row (right to left)
- Extract left column (bottom to top, skipping corners)
Concatenate these four parts into one string.
Then, we append the first 3 characters of this string to itself and count how many times 
"1543" appears in it — to handle wraparound patterns that span across layer boundaries.

This approach processes each cell once per layer it belongs to.
"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [input() for _ in range(n)]
    t = 0
    L = min(n, m) // 2  # Number of layers to process
    for i in range(L):
        # Extract top row from left to right
        p1 = g[i][i : m - i]
        # Extract right column from top to bottom (excluding corners)
        p2 = "".join(g[j][m - i - 1] for j in range(i + 1, n - i - 1))
        # Extract bottom row from right to left
        p3 = g[n - i - 1][i : m - i][::-1]
        # Extract left column from bottom to top (excluding corners)
        p4 = "".join(g[j][i] for j in range(i + 1, n - i - 1))[::-1]
        # Concatenate all four parts to form the layer's spiral string
        s = p1 + p2 + p3 + p4
        # Append first 3 characters to handle wraparound cases (e.g., last few chars 
        # of current layer may match with start of next)
        t += (s + s[:3]).count("1543")
    print(t)


# https://github.com/VaHiX/codeForces/