# Problem: CF 2138 E1 - Determinant Construction (Easy Version)
# https://codeforces.com/contest/2138/problem/E1

"""
Constructs a square matrix M such that:
- The determinant of M is equal to x.
- Each element of M is either -1, 0, or 1.
- The side length of M is at most 80.
- Each row and column has at most 3 non-zero entries.

Algorithm:
The construction uses a recursive-like approach based on bit manipulation:
- For x = 0, return [[0]].
- For x > 0:
    - Compute k = x.bit_length() (number of bits needed to represent x).
    - Set n = 3 * k + 1 (size of matrix).
    - Build a block structure where each bit of x determines how the matrix is extended.
    - Use specific patterns for each row/column to encode the value of x.

Time Complexity: O(k^2), where k = x.bit_length(), since we build a matrix of size ~3k × 3k.
Space Complexity: O(k^2), for storing the matrix of size ~3k × 3k.
"""

def construct_cf_matrix(x):
    if x == 0:
        return [[0]]
    k = x.bit_length()
    n = 3 * k + 1
    M = [[0] * n for _ in range(n)]
    for i in range(k):
        r = 2 * i
        c = 2 * i
        M[r][c] = 1
        M[r][c + 1] = -1
        M[r + 1][c] = 1
        M[r + 1][c + 1] = 1
        M[r + 2][c + 1] = 1
        if (x >> i) & 1:  # If the i-th bit of x is set
            M[2 * i + 1][2 * k + i + 1] = 1 if i % 2 == 0 else -1  # Set specific entry based on parity
    for i in range(2 * k + 1, n):
        M[i][i - 1] = 1
        M[i][i] = 1
    return M


t = int(input())
for _ in range(t):
    x = int(input())
    M = construct_cf_matrix(x)
    print(len(M))
    for row in M:
        print(" ".join(str(v) for v in row))


# https://github.com/VaHiX/codeForces/