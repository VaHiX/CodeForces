# Problem: CF 1710 A - Color the Picture
# https://codeforces.com/contest/1710/problem/A

# ==================================================================
# Problem: Color the Picture
# Algorithms/Techniques: Greedy, Binary Search, Sorting
# Time Complexity: O(k * log(k) + t * k * log(max(a)))
# Space Complexity: O(k)
# ==================================================================

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().strip()
out = []


def calc(r, c):
    # Check if we can color a grid of size r x c with given pigments
    for i in range(k - 1, -1, -1):  # Iterate from largest to smallest pigment
        if a[i] // r > 1:  # If this pigment can cover more than one row
            c -= a[i] // r  # Reduce the required cells by how many full rows it covers
        if c == 1 and (a[-1] // r < 3 or max(a[:i], default=0) // r < 2):
            # If only 1 cell remains but we can't fulfill min requirement, return 0
            return 0
    return c < 1  # Return if all cells have been covered


for _ in range(int(input())):
    n, m, k = map(int, input().split())
    a = array("i", sorted([int(x) for x in input().split()]))
    out.append("Yes" if calc(n, m) or calc(m, n) else "No")
print("\n".join(out))


# https://github.com/VaHiX/codeForces/