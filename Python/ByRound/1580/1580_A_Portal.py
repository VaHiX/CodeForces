# Problem: CF 1580 A - Portal
# https://codeforces.com/contest/1580/problem/A

"""
Algorithm: Rectangle Inspection with Prefix Sums
Time Complexity: O(n^2 * m^2) where n and m are dimensions of the input matrix
Space Complexity: O(n * m) for prefix sum arrays

This solution finds the minimum number of operations to form a valid "portal" 
in the given rectangle. A portal is defined by specific conditions on borders 
and interior. The approach uses prefix sums to quickly query the number of 
operations needed to create a valid portal of a certain size. It iterates over 
all possible top-left and bottom-right coordinates of a 5x4 or larger rectangle 
and computes the required changes using prefix sums.

The function `v` calculates the number of 0s or 1s in a subrectangle using 
prefix sums, depending on the flag. It is used to count the number of 
changes needed in different parts of the candidate portal.
"""

import sys

T = int(sys.stdin.readline().strip())


def v(is0, is1, x, y, a, b, flag):
    # Function to calculate sum of values in a subrectangle using prefix sums
    # flag = 1 means count 1s, otherwise count 0s
    if flag == 1:
        g = is1
    else:
        g = is0
    return g[a + 1][b + 1] + g[x][y] - g[a + 1][y] - g[x][b + 1]


for t in range(T):
    n, m = list(map(int, sys.stdin.readline().strip().split(" ")))
    mat = []
    for i in range(n):
        mat.append(sys.stdin.readline().strip())
    
    # Create prefix sum arrays for 0s and 1s
    is1 = [[0 for j in range(m + 1)] for i in range(n + 1)]
    is0 = [[0 for j in range(m + 1)] for i in range(n + 1)]
    
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            # Build prefix sum array for 1s
            is1[i][j] = (
                is1[i - 1][j]
                + is1[i][j - 1]
                - is1[i - 1][j - 1]
                + int(mat[i - 1][j - 1] == "1")
            )
            # Build prefix sum array for 0s
            is0[i][j] = (
                is0[i - 1][j]
                + is0[i][j - 1]
                - is0[i - 1][j - 1]
                + int(mat[i - 1][j - 1] == "0")
            )
    
    res = 16  # Initialize with a large value
    
    # Try all combinations of top-left and bottom-right coordinates
    for i in range(n):
        for j in range(m):
            # Iterate over possible bottom rows (a)
            for a in range(i + 4, n):
                # Calculate cost for left border (vertical edges)
                left = v(is0, is1, i + 1, j, a - 1, j, 0)
                if left >= res:
                    break  # Early termination if not promising
                
                # Iterate over possible right columns (b)
                for b in range(j + 3, m):
                    # Cost for top border (horizontal edges)
                    up = v(is0, is1, i, j + 1, i, b - 1, 0)
                    r = left + up
                    if r >= res:
                        break  # Early termination
                    
                    # Cost for bottom border (horizontal edges)
                    down = v(is0, is1, a, j + 1, a, b - 1, 0)
                    r += down
                    if r >= res:
                        break  # Early termination
                    
                    # Cost for interior (filling middle part)
                    mid = v(is0, is1, i + 1, j + 1, a - 1, b - 1, 1)
                    r += mid
                    if r >= res:
                        break  # Early termination
                    
                    # Cost for right border (vertical edges)
                    right = v(is0, is1, i + 1, b, a - 1, b, 0)
                    r += right
                    
                    # Update minimum operations if better result found
                    if r < res:
                        res = r
                        
    print(res)


# https://github.com/VaHiX/CodeForces/