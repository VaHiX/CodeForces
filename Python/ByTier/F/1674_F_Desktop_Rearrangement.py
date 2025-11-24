# Problem: CF 1674 F - Desktop Rearrangement
# https://codeforces.com/contest/1674/problem/F

"""
Code Purpose:
This code solves the problem of maintaining a "good" arrangement of icons on a desktop after a series of icon additions or removals.
A desktop arrangement is considered "good" if all icons form a shape that is a prefix of full columns, followed by a prefix of the next column.
The approach uses an optimized view of the desktop by flattening it column-wise into a 1D array, which allows efficient tracking of icon positions with O(1) updates.
It tracks:
- Total number of icons (`tot`)
- Number of icons in the prefix columns (`inner`)
For each query:
- If an icon is removed, we adjust `tot` and `inner`
- If an icon is added, we adjust `tot` and `inner`
- The number of moves required is calculated as `tot - inner`.

Algorithms/Techniques:
- Column-wise flattening of the 2D matrix for easier processing
- Efficient tracking of prefix columns and partial column
- Constant time update for each operation (O(1))

Time Complexity: O(n * m + q)
Space Complexity: O(n * m)
"""

from itertools import chain

I = lambda: map(int, input().split())
n, m, q = I()
g0 = [list(input()) for _ in range(n)]
# Flatten the grid column-wise into a 1D array
g = list(chain.from_iterable(zip(*g0)))
tot = g.count("*")  # Total number of icons
inner = g[:tot].count("*")  # Number of icons in prefix columns

for _ in range(q):
    i, j = I()
    p = (j - 1) * n + i - 1  # Index in flattened array
    if g[p] == "*":  # Removing an icon
        tot -= 1
        # If the last icon in the flattened array was an icon, we remove it from inner count
        if g[tot] == "*":
            inner -= 1
        # If the removed icon was in the prefix, adjust inner count
        if p < tot:
            inner -= 1
        g[p] = "."  # Mark cell as empty
    else:  # Adding an icon
        g[p] = "*"  # Mark cell as occupied
        # If the last icon in the flattened array was an icon, we add it to inner count
        if g[tot] == "*":
            inner += 1
        # If the new icon was placed in the prefix, adjust inner count
        if p < tot:
            inner += 1
        tot += 1  # Increment total icon count
    print(tot - inner)  # Minimum moves = total icons - prefix icons


# https://github.com/VaHiX/CodeForces/