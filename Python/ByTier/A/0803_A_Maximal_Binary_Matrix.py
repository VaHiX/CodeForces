# Problem: CF 803 A - Maximal Binary Matrix
# https://codeforces.com/contest/803/problem/A

"""
Algorithm: Maximal Binary Matrix
Approach:
- Fill the matrix in a way to maximize lexicographically while maintaining symmetry.
- Start filling from the top-left, and place 1s in symmetric pairs (i,j) and (j,i).
- For diagonal elements (i == j), place only one 1.
- Prioritize placing 1s in higher positions to get lexicographically maximal result.

Time Complexity: O(n^2) - We iterate through the matrix once to fill it.
Space Complexity: O(n^2) - We store the n x n matrix.
"""

import sys

n, k = [int(i) for i in input().split()]
s = [n * ["0"] for i in range(n)]
if k > n * n:
    print(-1)
    sys.exit()
heng = 0  # row index
zong = 0  # column index
while k > 0:
    # If we are on the diagonal, place only one 1
    if heng == zong:
        k -= 1
        s[heng][zong] = "1"
    # If we are not on the diagonal and have more than 1 to place, place two 1s symmetrically
    elif heng != zong and k != 1:
        k -= 2
        s[heng][zong] = "1"
        s[zong][heng] = "1"
    zong += 1
    # Move to next row if we've reached the end of current row
    if zong == n:
        heng += 1
        zong = heng
for i in range(n):
    h = str(s[i])
    print(" ".join(s[i]))


# https://github.com/VaHiX/CodeForces/