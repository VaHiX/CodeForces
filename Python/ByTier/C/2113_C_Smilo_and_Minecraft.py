# Problem: CF 2113 C - Smilo and Minecraft
# https://codeforces.com/contest/2113/problem/C

"""
C. Smilo and Minecraft

Purpose:
This code solves a problem where Smilo places dynamite in empty cells of a grid to blast away gold ore.
When dynamite explodes at position (x, y), it affects all cells within a square of side 2k+1 centered at (x,y).
Gold ore inside the explosion area is removed unless it's on the boundary of the square, where it gets collected.

Algorithms/Techniques:
- Prefix sum technique to quickly calculate submatrix sums.
- Brute-force over all empty positions to try detonation and compute resulting gold gained.
- For each possible blast position, determine how many gold pieces are on the boundary and not removed.

Time Complexity: O(n * m * k)
Space Complexity: O(n * m)

The prefix sum array allows for O(1) query time of submatrix sums, so the overall complexity
is dominated by trying all positions (n * m) and for each doing a constant number of operations
using the prefix sums.

"""

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print


def f(i, j, k):
    # Calculate boundaries of the explosion square around (i,j)
    p, q, r, s = min(i + k, n), max(i - k - 1, 0), min(j + k, m), max(j - k - 1, 0)
    # Use prefix sum to get the count of gold in that submatrix
    return a[p][r] - a[p][s] - a[q][r] + a[q][s]


for _ in range(int(R())):
    n, m, k = S()
    a = [[0] * (m + 1) for _ in range(n + 1)]
    b = [R().strip() for _ in range(n)]
    # Build prefix sum array
    for i in range(n):
        for j in range(m):
            if b[i][j] == "g":
                a[i + 1][j + 1] = 1
            a[i + 1][j + 1] += a[i + 1][j] + a[i][j + 1] - a[i][j]
    
    # Total gold in the grid
    r = a[n][m]
    # Try placing dynamite at every empty cell
    for i in range(n):
        for j in range(m):
            if b[i][j] == ".":
                # Find the minimum gold that we could lose by placing dynamite at (i+1, j+1)
                r = min(r, f(i + 1, j + 1, k - 1))
    # Maximum gold obtained = total_gold - minimum loss
    P(a[n][m] - r)


# https://github.com/VaHiX/CodeForces/