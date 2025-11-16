# Problem: CF 2160 E - Rectangles
# https://codeforces.com/contest/2160/problem/E

"""
Algorithm: Rectangle Area Minimization
Approach:
- For each possible top row u and bottom row d (u < d), we scan columns from left to right.
- When both cells (u, c) and (d, c) are 1, we consider this column as a potential part of a rectangle.
- We track the last such column where both u and d rows have 1s.
- When we find a new valid column after the previous one, calculate the area of the rectangle formed.
- Store the minimum area in mas[d][y] for all columns y in the range.
- For each row, propagate the minimum areas from below upward to ensure correct propagation.
- If the grid is taller than it is wide, transpose the grid for optimization.
- Output the results in the original orientation.

Time Complexity: O(n^2 * m) where n and m are dimensions of the grid.
Space Complexity: O(n * m) for storing the grid and the result matrix.
"""

import sys


def solve():
    data = sys.stdin.read().strip().split()
    it = iter(data)
    t = int(next(it))
    for _ in range(t):

        def transp(n1, m1, mapa1):
            # Transpose the grid: swap rows and columns
            transposed = [[0] * n1 for _ in range(m1)]
            for i0 in range(n1):
                for j0 in range(m1):
                    transposed[j0][i0] = mapa1[i0][j0]
            return transposed

        n, m = int(next(it)), int(next(it))
        mapa = [[0 for j in range(m)] for i in range(n)]
        for i in range(n):
            s = next(it)
            for j in range(m):
                mapa[i][j] = int(s[j])
        transposed = m < n  # If grid is taller than wider, transpose for better performance
        if transposed:
            mapa = transp(n, m, mapa)
            n, m = m, n

        mas = [[10**10 for j in range(m)] for i in range(n)]  # Initialize with large value

        # For each pair of rows (u, d) where u < d
        for u in range(n - 1):
            for d in range(u + 1, n):
                last = None
                # Scan columns from left to right
                for c in range(m):
                    # If both current cells are 1
                    if mapa[u][c] == 1 and mapa[d][c] == 1:
                        if last != None:
                            # Calculate area of rectangle formed
                            s = (d - u + 1) * (c - last + 1)
                            # Update the minimum area in this rectangle's span
                            for y in range(last, c + 1):
                                mas[d][y] = min(mas[d][y], s)
                        last = c
            # Propagate the minimum areas upwards
            for d in reversed(range(u, n - 1)):
                for c in range(m):
                    mas[d][c] = min(mas[d][c], mas[d + 1][c])

        # Replace large values with 0 for cells that cannot form valid rectangles
        for i in range(n):
            for j in range(m):
                if mas[i][j] == 10**10:
                    mas[i][j] = 0
        if transposed:
            # Transpose the result matrix back to original orientation
            mas = transp(n, m, mas)
        for l in mas:
            print(" ".join(map(str, l)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/