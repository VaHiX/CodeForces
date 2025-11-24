# Problem: CF 2138 E2 - Determinant Construction (Hard Version)
# https://codeforces.com/contest/2138/problem/E2

"""
E2. Determinant Construction (Hard Version)
time limit per test5 seconds
memory limit per test256 megabytes

This is the hard version of the problem. The difference between the versions is that in this version, the constraints on the side length of
M
is smaller and the constraints on
t
is larger. You can hack only if you solved all versions of this problem.

You are given a non-negative integer
x
. Your task is to construct a square matrix
M
that satisfies all of the following conditions:
The side length of
M
is at most
50
.
Each element of
M
is either
−1
,
0
, or
1
.
The determinant of
M
is equal to
x
.
Each row of
M
can have at most
3
non-zero positions, and each column of
M
can have at most
3
non-zero positions.
It can be proven that such a matrix always exists.

Algorithms/Techniques:
- The algorithm uses a greedy heuristic approach combined with backtracking to generate a valid matrix that satisfies the determinant constraint.
  - The process starts by attempting construction from a known initial value (based on golden ratio approximation for x>1).
  - If that fails, it tries incrementing the y-coordinate until valid solution is found.
  - The key idea uses recursive-like structure to modify small submatrices and build up to full matrix.

Time Complexity: O(t * n^2) where t is number of test cases and n <= 50
Space Complexity: O(n^2) for storing the matrix, where n <= 50
"""

import math

maxn = 50


def attempt(x, y):
    gr = [[0] * maxn for _ in range(maxn)]
    n = maxn
    while 1:
        # If x > y, modify matrix and swap coordinates accordingly.
        if x > y:
            gr[n - 1][n - 1] = 1
            gr[n - 1][n - 2] = 1
            gr[n - 2][n - 1] = -1
            x, y = y, x - y
        # If x < y, perform specific transformations based on the difference.
        elif x < y:
            if y - x < x:
                gr[n - 1][n - 1] = 0
                gr[n - 1][n - 2] = 1
                gr[n - 2][n - 1] = -1
                x, y = y, x
            else:
                gr[n - 1][n - 1] = 1
                gr[n - 1][n - 2] = 1
                gr[n - 2][n - 1] = 1
                x, y = y, y - x
        # If x equals 1, fill diagonal with ones to terminate.
        elif x == 1:
            for i in range(n):
                gr[i][i] = 1
            break
        else:
            # For values where x > 1, use approximation involving the golden ratio.
            gr[n - 1][n - 1] = 1
            y = math.floor(x * ((5**0.5) - 1) / 2 + 0.5)
        # If n becomes less than two, return [-1] indicating failure.
        if n < 2:
            return [-1]
        n -= 1
    return gr


for _ in range(int(input())):
    x = int(input())
    # Initialize y based on heuristic for determining starting point in construction.
    y = 1 if x == 1 else math.floor(x * ((5**0.5) - 1) / 2 + 0.5)
    gr = [-1]
    # Tries different values of y until a valid matrix is returned.
    while len(gr) == 1:
        gr = attempt(x, y)
        y += 1
    print(maxn)
    print("\n".join([" ".join([str(j) for j in i]) for i in gr]))


# https://github.com/VaHiX/codeForces/