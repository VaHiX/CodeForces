# Problem: CF 1982 D - Beauty of the mountains
# https://codeforces.com/contest/1982/problem/D

"""
Algorithm: 
This code solves a problem involving balancing the sums of two types of mountains (snowy caps vs. no caps) on a 2D grid by applying k×k submatrix transformations. 
The key idea is to model the problem using a system of linear equations where each transformation contributes a coefficient to the difference between sums of the two types. 
By computing all possible coefficients from submatrices and their net effect on the sum difference, we analyze whether it's possible to reach equality by choosing appropriate constants for transformations.

Time Complexity: O(n^2 * m^2 * log(max_coeff)) per test case
Space Complexity: O(n * m + n * m) = O(n * m) for prefix sums and coefficient storage
"""

import os
import sys

if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")

else:
    pass


input = sys.stdin.readline


def solve():

    n, m, k = list(map(int, input().split()))

    hgts = [list(map(int, input().split())) for i in range(n)]
    tpp = [input().strip() for i in range(n)]

    # Prefix sum array to quickly compute number of '1's in any submatrix
    ones = [[0] * (m + 1) for i in range(n + 1)]
    for i in range(n):
        for j in range(m):
            ones[i + 1][j + 1] = (
                ones[i + 1][j] + ones[i][j + 1] - ones[i][j] + (tpp[i][j] == "1")
            )

    # Collect all coefficients from k x k transformations
    coeffs = []
    for i in range(n - k + 1):
        for j in range(m - k + 1):
            # Count number of '1's in this k x k matrix
            cur = ones[i + k][j + k] - ones[i + k][j] - ones[i][j + k] + ones[i][j]
            # We add cur (number of type 1) and (k*k - cur) (number of type 0)
            # But we're interested in the difference, so it's: (number of 1s - (k*k - number of 1s)) = 2*cur - k*k  
            coeffs.append(cur - (k * k - cur))

    # Compute required change to balance the sums
    need = 0
    for i in range(n):
        for j in range(m):
            # We use -1 for type 1 (mountains without caps),
            # and 1 for type 0 (mountains with caps).
            # So we are computing sum of (1s) - sum of (0s).
            need += ((-1, 1)[tpp[i][j] == "1"]) * hgts[i][j]

    # Compute GCD of all coefficients
    g = 0
    from math import gcd

    for i in coeffs:
        g = gcd(g, i)

    # If need is 0 or it's divisible by GCD, then it's possible to achieve balance.
    if (need == 0) or (g != 0 and need % g == 0):
        print("YES")
    else:
        print("NO")


tt = 1
tt = int(input())
for _ in range(tt):
    solve()


# https://github.com/VaHiX/CodeForces/