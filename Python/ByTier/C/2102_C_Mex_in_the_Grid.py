# Problem: CF 2102 C - Mex in the Grid
# https://codeforces.com/contest/2102/problem/C

"""
C. Mex in the Grid

Algorithm: Spiral Fill
Approach: 
  - Fill a grid of size n x n with integers from 0 to n^2 - 1 in a spiral pattern starting from the center.
  - This spiral arrangement ensures that smaller values are grouped together, which maximizes MEX across subgrids.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

The code fills the grid in a clockwise spiral pattern beginning at the center of the grid. 
It uses a step-based approach where the number of steps increases every two directions (after moving right and down).
This strategy attempts to distribute low values close together to optimize MEX.
"""

for _ in range(int(input())):
    n = int(input())
    m = [[0] * n for _ in range(n)]
    g = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Right, Down, Left, Up
    i = j = n // 2
    if n % 2 == 0:
        i -= 1
        j -= 1
    val = 0
    m[i][j] = val
    val += 1
    step = 1
    while val < n * n:
        for d in range(4):
            x, y = g[d]
            for _ in range(step):
                if val >= n * n:
                    break
                i += x
                j += y
                if 0 <= i < n and 0 <= j < n:
                    m[i][j] = val
                    val += 1
            if d % 2 == 1:  # After moving down and up, increase step size
                step += 1
    res = []
    for row in m:
        res.append(" ".join(map(str, row)))
    print("\n".join(res))


# https://github.com/VaHiX/codeForces/