# Problem: CF 1895 F - Fancy Arrays
# https://codeforces.com/contest/1895/problem/F

"""
Algorithm: Dynamic Programming with Matrix Exponentiation
Purpose: Count the number of "fancy" arrays of length n, where:
         1. At least one element from the range [x, x+k-1] appears in the array
         2. Each consecutive pair of elements differ by at most k
Time Complexity: O(k^3 * log(n)) due to matrix exponentiation
Space Complexity: O(k^2) for the transition matrix and O(k) for the result vector

The solution uses matrix exponentiation to efficiently compute transitions
between states. It computes the number of valid partial arrays of length n,
then subtracts those that don't contain any value in [x, x+k-1].
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())

mod = 10**9 + 7


def mat_mul(X, Y):
    # Multiply two matrices X and Y modulo mod
    n, m = len(X), len(Y[0])
    res = [[0 for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            for k in range(len(Y)):
                res[i][j] += X[i][k] * Y[k][j]
                res[i][j] %= mod
    return res


def solve(n, k, x):
    mod = 10**9 + 7
    # Base case: All arrays of length n-1 where each element is in [0, 2k]
    # Multiply by (x + k) since first element can be in [0, x + k]
    res = pow(2 * k + 1, n - 1, mod) * (x + k) % mod

    if x == 0:
        # If x is 0, then all values are valid from 0 to k-1, so we don't subtract anything
        return res

    # Create transition matrix A for states [0, x-1]
    # A[i][j] = 1 means we can go from state i to state j with difference at most k
    A = [[0] * x for i in range(x)]
    for i in range(x):
        for j in range(x):
            if abs(i - j) <= k:
                A[i][j] = 1

    # Identity matrix for exponentiation
    E = [[1] for _ in range(x)]
    t = n - 1
    while t:
        if t & 1:
            E = mat_mul(A, E)
        A = mat_mul(A, A)
        t >>= 1

    # Subtract invalid paths (no value from [x, x+k-1] appears)
    for i in range(x):
        res -= E[i][0]
        res %= mod

    return res


for _ in range(int(input())):
    n, x, k = mi()
    print(solve(n, k, x))


# https://github.com/VaHiX/CodeForces/