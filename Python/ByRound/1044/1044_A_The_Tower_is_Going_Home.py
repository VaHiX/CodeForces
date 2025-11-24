# Problem: CF 1044 A - The Tower is Going Home
# https://codeforces.com/contest/1044/problem/A

"""
Problem: A. The Tower is Going Home

Algorithms/Techniques: Two-pointer technique, sorting, greedy approach

Time Complexity: O(n log n + m log m)
Space Complexity: O(n + m)

The task is to find the minimum number of spells to remove so that a rook at (1,1) can reach the top row (row 10^9).
- Vertical spells block columns between x and x+1
- Horizontal spells block segments in rows from x1 to x2

Approach:
1. Sort vertical spells by column position
2. Collect only horizontal spells that start from column 1 (as rook starts there)
3. For each vertical spell, use two pointers to find how many horizontal spells are above it
4. The minimum answer is the minimum number of spells to remove across all possible configurations
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
inf = 10**9
m, n = mii()
vert = [ii() for _ in range(m)]
vert.sort()
vert.append(inf)  # Add infinity to handle edge case
hori = []
for _ in range(n):
    x1, x2, y = mii()
    if x1 == 1:  # Only consider horizontal spells starting from column 1
        hori.append(x2)
hori.sort()  # Sort horizontal spell ends
n = len(hori)
ans = n  # Initialize with all horizontal spells removed
j = 0  # Pointer for horizontal spells

# For each vertical spell, compute the minimum number of horizontal spells to remove
for i, x in enumerate(vert):
    while j < n and hori[j] < x:  # Move pointer to skip overlapping horizontal spells
        j += 1
    ans = min(ans, i + n - j)  # i = vertical spells to remove, n-j = horizontal spells to remove

print(ans)


# https://github.com/VaHiX/codeForces/