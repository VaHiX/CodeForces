# Problem: CF 1575 K - Knitting Batik
# https://codeforces.com/contest/1575/problem/K

# ==============================================================================
# Problem: K. Knitting Batik
# Purpose: Count valid batik color combinations where two given sub-rectangles have same pattern.
# Algorithms/Techniques:
#   - Modular Exponentiation (pow with modulo)
#   - Combinatorics and counting principles
# Time Complexity: O(log(max(n,m))) due to modular exponentiation
# Space Complexity: O(1) - only using a few variables
# ==============================================================================

p = 10**9 + 7  # Modulo value
n, m, k, r, c = [int(x) for x in input().split()]  # Read grid dimensions, colors, and sub-rectangle size
ax, ay, bx, by = [int(x) for x in input().split()]  # Read top-left corners of two sub-rectangles

# If the two rectangles are not at the same position,
# we calculate number of color combinations where they must be equal.
# This means we count combinations for all cells except shared rectangle area.
if [ax, ay] != [bx, by]:
    answer = pow(k, n * m - r * c, p)  # Modular exponentiation to compute k^(total_cells - shared_cells)
else:
    # If the rectangles are at the same position,
    # we only need to compute combinations for entire grid.
    answer = pow(k, n * m, p)  # Modular exponentiation to compute k^(n*m)

print(answer)


# https://github.com/VaHiX/codeForces/