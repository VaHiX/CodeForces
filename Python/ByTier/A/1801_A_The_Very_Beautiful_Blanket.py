# Problem: CF 1801 A - The Very Beautiful Blanket
# https://codeforces.com/contest/1801/problem/A

"""
Code Purpose:
This code generates a beautiful blanket matrix B of size n x m such that for every 4x4 submatrix,
the XOR of the four corners of the top-left and bottom-right quadrants are equal, and the XOR of 
the four corners of the top-right and bottom-left quadrants are equal. The matrix uses distinct 
integers to maximize the number of different values.

Algorithms/Techniques:
- The approach uses a simple pattern-based encoding: for each cell (i, j), the value is calculated as i * 256 + j.
- This ensures all values are distinct and maximizes the number of unique integers in the matrix.
- The pattern is chosen to satisfy the property of the beautiful blanket by construction.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

The key insight is that using a simple linear function like i * 256 + j produces enough variation 
to ensure all values are unique and the constraints are satisfied.
"""

for l in [*open(0)][1:]:
    n, m = map(int, l.split())
    print(n * m, *[i * 256 + j for i in range(n) for j in range(m)])


# https://github.com/VaHiX/CodeForces/